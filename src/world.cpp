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
#include "state.h"

using namespace std;

GameWorld::GameWorld(SDL_Renderer *renderer, GameState *istate, Toolbar* itoolbar) 
    : Renderable(renderer) {
    state = istate;
    toolbar = itoolbar;

    hover = new Sprite(renderer, HOVER_TEXTURE_FILE, SDL_BLENDMODE_ADD);

    initHexs({5,6}, 6);
}

void GameWorld::initHexs(SDL_Point origin, int size) {
    hexs.clear();

    int i,x,y1,y2,xfrom,xto;
    for (i=0;i<size;++i) {
        y1 = origin.y-i;
        y2 = origin.y+i;
        xfrom = origin.x-size+1+((i+(origin.y%2))/2);
        xto = origin.x+size-1-((i+((origin.y+1)%2))/2);
        for (x=xfrom;x<=xto;++x) {
            hexs.insert({x,y1});
            hexs.insert({x,y2});
        }
    }

    hexs.begin();
}

GameWorld::~GameWorld() {
    delete hover;

    Sprite::clearTextureCache();
}

void GameWorld::OnClick(SDL_MouseButtonEvent* event) {
    SDL_Point coord = coordsForXY({event->x, event->y});
    Thing* thing;

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

    LOG(DEBUG, "Updating neighbors");
    thing = state->getThing(coord);
    updateNeighbors(neighbors, thing);
}

void GameWorld::useTool(SDL_Point coord) {
    Tile* ground = state->getGround(coord);
    Thing* thing = state->getThing(coord);
    NeighborArray neighbors = Utils::getNeighbors(coord);

    switch (toolbar->getActive()) {
    case ToolType::GRASS:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set GRASS");
            state->setGround(coord, Tile::getTile(GRASS, renderer));
        }
        break;
    case ToolType::WATER:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set WATER");
            state->setGround(coord, Tile::getTile(WATER, renderer));
        }
        break;
    case ToolType::DIRT:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set DIRT");
            state->setGround(coord, Tile::getTile(DIRT, renderer));
        }
        break;
    case ToolType::SAND:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set SAND");
            state->setGround(coord, Tile::getTile(SAND, renderer));
        }
        break;
    case ToolType::ROAD:
        if (ground!=NULL && ground->isContainer() && thing==NULL) {
            LOG(DEBUG, "Put ROAD");
            state->putThing(coord, createRoad(neighbors));
        }
        break;
    case ToolType::BUILDING:
        if (ground!=NULL && ground->isContainer()) {
            if (thing==NULL) {
                LOG(DEBUG, "Create ThingStack");
                thing = new Building(renderer);
                state->putThing(coord, thing);
            }
            if(thing->getType()==STACK) {
                LOG(DEBUG, "Create BuildingSegment");
                ((Building*) thing)->grow();
            }
        }
        break;
    case ToolType::DESTROY:
        LOG(DEBUG, "Destroy!");
        if (state->countThings(coord) > 0) {
            LOG(DEBUG, "Oh, there's a thing! Destroy!");
            state->clearThing(coord);
        } else if (ground != NULL) {
            LOG(DEBUG, "Oh, there's ground! Destroy!");
            state->removeGround(coord);
        }
        break;
    default:
        //idle
        break;
    }
}

void GameWorld::updateNeighbors(NeighborArray neighbors, Thing* thing) {
    Thing* neighbor;
    SDL_Point coord;
    Direction dir = (Direction)0;

    LOG(DEBUG, "Update neighbors");

    while (dir<6) {
        coord = neighbors[dir];
        neighbor = state->getThing(coord);
        if (neighbor != NULL) {
            switch (neighbor->getType()) {
            case ROAD:
                ((Road*)neighbor)->setSegmentVisible(
                    (Direction)((3+dir)%6), thing!=NULL);
                break;
            default:
                break;
            }
        }
        dir = (Direction) (((int) dir) + 1);
    }
}

Road* GameWorld::createRoad(NeighborArray neighbors) {
    LOG(DEBUG, "Create Road");
    Road* road = new Road(renderer);

    updateRoad(road, neighbors);

    return road;
}

void GameWorld::updateRoad(Road* road, NeighborArray neighbors) {
    Thing* neighbor;
    Direction dir=(Direction)0;

    LOG(DEBUG, "Update Road");

    while (dir<6) {
        neighbor = state->getThing(neighbors[dir]);
        road->setSegmentVisible(dir, neighbor!=NULL);
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
            if ((norm.x * 2 / HEX_W) * HEX_H / 4 <= norm.y) {
                --ret.y;
                ret.x += row_odd-1;
            }
        } else if (norm.x > HEX_W / 2) {
            if (((HEX_W-norm.x) * 2 / HEX_W) * HEX_H / 4 <= norm.y) {
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
}

void GameWorld::drawHexOutline(SDL_Point coord) {
    const int POINTS_COUNT = 7;
    int x = (HEX_W/2) + (coord.x)*HEX_W+(coord.y%2)*(HEX_W/2);
    int y = (HEX_H/2) + (coord.y*((HEX_H*3)/4));

    if (state->isGround(coord)) {
        SDL_Color color;
        try {
            color = tileBorderColors.at(state->getGround(coord)->getType());
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        } catch (const out_of_range& oor) {
            SDL_SetRenderDrawColor(renderer, 0x89, 0x92, 0x9f, 255);
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 0xc4, 0xe0, 0xf2, 255);
    }

    SDL_Point points[POINTS_COUNT] = {
        {x-(HEX_W/2), y-(HEX_H/4)},
        {x          , y-(HEX_H/2)},
        {x+(HEX_W/2), y-(HEX_H/4)},
        {x+(HEX_W/2), y+(HEX_H/4)},
        {x          , y+(HEX_H/2)},
        {x-(HEX_W/2), y+(HEX_H/4)},
        {x-(HEX_W/2), y-(HEX_H/4)}
    };

    if (!state->isGround(coord)) {
        SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
    }
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

void GameWorld::drawHex(SDL_Point coord) {
    SDL_Rect DestR;
    Tile* ground = NULL;
    Thing* thing = NULL;

    DestR.x = (coord.x)*HEX_W+(coord.y%2)*(HEX_W/2);
    DestR.y = (coord.y*((HEX_H*3)/4));
    DestR.w = HEX_W;
    DestR.h = HEX_H;

    ground = state->getGround(coord);
    if (ground != NULL) {
        ground->render(&DestR);
    }

    drawHexOutline(coord);

    thing = state->getThing(coord);
    if (thing != NULL) {
        thing->render(&DestR);
        //DestR.y -= thing->height;
        //DestR.h += thing->height;
    }

    drawHover(coord, &DestR);
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
