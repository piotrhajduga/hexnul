#include <unordered_map>
#include <functional>
#include <iostream>

#include "SDL.h"

#include "utils.h"
#include "renderable.h"
#include "sprite.h"
#include "thing.h"
#include "tile.h"
#include "building.h"
#include "road.h"
#include "direction.h"
#include "world.h"
#include "toolbar.h"
#include "agent.h"
#include "state.h"

using namespace std;

GameWorld::GameWorld(SDL_Renderer *renderer, GameState *istate, Toolbar* itoolbar) 
    : Renderable(renderer) {
    state = istate;
    toolbar = itoolbar;

    hover = new Sprite(renderer, HOVER_TEXTURE_FILE, SDL_BLENDMODE_ADD);
    empty = new Sprite(renderer, EMPTY_TEXTURE_FILE);

    initHexs({VIEW_RADIUS-1,VIEW_RADIUS}, VIEW_RADIUS);
}

Tile* GameWorld::generateRandomTile() {
    int randint = rand() % 4;
    return new Tile(TileType(randint), renderer);
}

void GameWorld::insertHex(SDL_Point coord) {
    int randint = rand() % 100;
    hexs.insert(coord);
    if (randint > 20) {
        state->setGround(coord, generateRandomTile());
    }
}

void GameWorld::initHexs(SDL_Point origin, int size) {
    hexs.clear();

    int i,x,y1,y2,xfrom,xto;
    xfrom = origin.x-size+1+((origin.y%2)/2);
    xto = origin.x+size-1-(((origin.y+1)%2)/2);
    for (x=xfrom;x<=xto;++x) {
        insertHex({x, origin.y});
    }
    for (i=0;i<size;++i) {
        y1 = origin.y-i;
        y2 = origin.y+i;
        xfrom = origin.x-size+1+((i+(origin.y%2))/2);
        xto = origin.x+size-1-((i+((origin.y+1)%2))/2);
        for (x=xfrom;x<=xto;++x) {
            insertHex({x,y1});
            insertHex({x,y2});
        }
    }

    hexs.begin();
}

GameWorld::~GameWorld() {
    delete empty;
    delete hover;

    if (agent != NULL) {
        delete agent;
    }

    Sprite::clearTextureCache();
}

void GameWorld::OnClick(SDL_MouseButtonEvent* event) {
    SDL_Point coord = coordsForXY({event->x, event->y});
    NeighborArray neighbors = Utils::getNeighbors(coord);

    if (hexs.find(coord) != hexs.end()) {
        switch (event->button) {
        case SDL_BUTTON_LEFT:
            useTool(coord);
            break;
        case SDL_BUTTON_RIGHT:
            toolbar->setActive(ToolType::NONE);
            break;
        default:
            //idle
            break;
        }
    }

    RoadNode* thing = dynamic_cast<RoadNode*>(state->getThing(coord));
    if (thing!=NULL) {
        updateRoadNode(thing, neighbors);
    }
    updateNeighbors(neighbors, thing);
}

void GameWorld::useTool(SDL_Point coord) {
    Tile* ground = state->getGround(coord);
    Thing* thing = state->getThing(coord);

    switch (toolbar->getActive()) {
    case ToolType::GRASS:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set GRASS");
            state->setGround(coord, new Tile(GRASS, renderer));
        }
        break;
    case ToolType::WATER:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set WATER");
            state->setGround(coord, new Tile(WATER, renderer));
        }
        break;
    case ToolType::DIRT:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set DIRT");
            state->setGround(coord, new Tile(DIRT, renderer));
        }
        break;
    case ToolType::SAND:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set SAND");
            state->setGround(coord, new Tile(SAND, renderer));
        }
        break;
    case ToolType::ROAD:
        if (ground!=NULL && ground->isContainer() && thing==NULL) {
            LOG(DEBUG, "Put ROAD");
            thing = new Road(renderer);
            state->putThing(coord, thing);
        }
        break;
    case ToolType::BUILDING:
        if (ground!=NULL && ground->isContainer()) {
            if (thing==NULL) {
                LOG(DEBUG, "Create Building");
                state->putThing(coord, new BuildingWithLevel(renderer));
            } else {
                BuildingWithLevel* building = dynamic_cast<BuildingWithLevel*>(thing);
                if (building!=NULL) {
                    building->incLevel();
                }
            }
        }
        break;
    case ToolType::AGENT:
        if (agent==NULL) {
            if (ground != NULL) {
                LOG(DEBUG, "Create new PathfindingAgent");
                agent = new PathfindingAgent(renderer, state, coord);
            }
        } else {
            agent->setDestination(coord);
        }
        break;
    case ToolType::DESTROY:
        LOG(DEBUG, "Destroy!");
        if (state->countThings(coord) > 0) {
            LOG(DEBUG, "Oh, there's a thing! Destroy!");
            state->clearThing(coord);
        //} else if (ground != NULL) {
            //LOG(DEBUG, "Oh, there's ground! Destroy!");
            //state->removeGround(coord);
        }
        break;
    default:
        //idle
        break;
    }
}

void GameWorld::updateNeighbors(NeighborArray neighbors, RoadNode* thing) {
    RoadNode* neighbor;
    SDL_Point coord;
    Direction dir = (Direction)0;

    LOG(DEBUG, "Update neighbors");

    while (dir<6) {
        coord = neighbors[dir];
        neighbor = dynamic_cast<RoadNode*>(state->getThing(coord));
        if (neighbor != NULL) {
            neighbor->setSegmentVisible((Direction)((3+dir)%6), thing!=NULL && thing->isVisible());
        }
        dir = (Direction) (((int) dir) + 1);
    }
}

void GameWorld::updateRoadNode(RoadNode* road, NeighborArray neighbors) {
    RoadNode* neighbor;
    Direction dir=(Direction)0;

    LOG(DEBUG, "Update RoadNode");
    while (dir<6) {
        neighbor = dynamic_cast<RoadNode*>(state->getThing(neighbors[dir]));
        road->setSegmentVisible(dir, neighbor!=NULL && neighbor->isVisible());
        dir = (Direction) (((int) dir) + 1);
    }
}

SDL_Point GameWorld::coordsForXY(SDL_Point point) {
    int row_odd = (point.y / GRID_ROW_H) % 2;
    int row_offset = row_odd * HEX_W / 2;

    SDL_Point norm;
    norm.x = (point.x - row_offset) % HEX_W;
    norm.y = point.y % GRID_ROW_H;

    SDL_Point ret;

    ret.y = point.y / GRID_ROW_H;
    ret.x = (point.x - row_offset) / HEX_W;

    if (norm.y < GRID_ROW_TOP_H) {
        if (norm.x < HEX_W / 2) {
            if ((norm.x * 2 / HEX_W) * HEX_H / 4 < norm.y) {
                --ret.y;
                ret.x += row_odd-1;
            }
        } else if (norm.x > HEX_W / 2) {
            if (((HEX_W-norm.x) * 2 / HEX_W) * HEX_H / 4 < norm.y) {
                --ret.y;
                ret.x += row_odd;
            }
        }
    }

    return ret;
}

void GameWorld::render(SDL_Rect* rect) {
    SDL_SetRenderDrawColor(renderer, 0x09, 0x12, 0x1f, 255);
    SDL_RenderFillRect(renderer, rect);

    for (auto it=hexs.begin();it!=hexs.end();++it) {
        drawHex(*it);
    }

    drawAgent();
}

void GameWorld::OnMouseMove(SDL_MouseMotionEvent* event) {
    setHover(coordsForXY({event->x, event->y}));
}

inline bool operator== (SDL_Point p1, SDL_Point p2) {
    return p1.x==p2.x && p1.y==p2.y;
}

void GameWorld::setHover(SDL_Point coord) {
    if (hoverCoord != NULL && *hoverCoord == coord) {
        return;
    } else {
        delete hoverCoord;
        hoverCoord = new SDL_Point(coord);
    }
}

SDL_Rect GameWorld::getHexRectForCoord(SDL_Point coord) {
    SDL_Rect rect;
    rect.x = (coord.x)*HEX_W+(coord.y%2)*(HEX_W/2);
    rect.y = (coord.y*((HEX_H*3)/4));
    rect.w = HEX_W;
    rect.h = HEX_H;
    return rect;
}

void GameWorld::drawHex(SDL_Point coord) {
    SDL_Rect rect = getHexRectForCoord(coord);
    Tile* ground = NULL;
    Thing* thing = NULL;

    ground = state->getGround(coord);
    if (ground != NULL) {
        ground->render(&rect);
    } else {
        empty->render(&rect);
    }

    thing = state->getThing(coord);
    if (thing != NULL) {
        thing->render(&rect);
    } else {
    }

    drawHover(coord, &rect);
}

void GameWorld::drawHover(SDL_Point coord, SDL_Rect* rect) {
    Sprite* myhover = NULL;
    if (hoverCoord != NULL && coord == *hoverCoord) {
        myhover = toolbar->getActiveToolSprite();
        if (myhover == NULL) {
            myhover = hover;
        }
        SDL_Texture* tx = myhover->getTexture();
        SDL_SetTextureAlphaMod(tx, 0x90);
        myhover->render(rect);
        SDL_SetTextureAlphaMod(tx, 0xff);
    }
}

void GameWorld::drawAgent() {
    SDL_Rect rect;
    if (agent != NULL) {
        rect = getHexRectForCoord(agent->getPosition());
        agent->render(&rect);
    }
}
