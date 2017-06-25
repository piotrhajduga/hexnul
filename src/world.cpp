#include <unordered_map>
#include <functional>
#include <iostream>

#include "time.h"
#include "SDL.h"

#include "constants.h"
#include "utils.h"
#include "renderable.h"
#include "sprite.h"
#include "thing.h"
#include "tile.h"
#include "building.h"
#include "road.h"
#include "direction.h"
#include "world.h"
#include "agent.h"
#include "toolbar.h"
#include "maploader.h"
#include "gamestate.h"

using namespace std;

GameWorld::GameWorld(SDL_Renderer *renderer, GameState *istate, Toolbar* itoolbar) 
    : Renderable(renderer) {
    srand(time(NULL));

    state = istate;
    toolbar = itoolbar;

    hover = new Sprite(renderer, TEXTURE_TILE_HOVER, SDL_BLENDMODE_ADD);
    empty = new Sprite(renderer, TEXTURE_TILE_EMPTY);
    goalSprite = new Sprite(renderer, TEXTURE_GOALPOST);
    goalSpriteActive = new Sprite(renderer, TEXTURE_GOALPOST_ACTIVE);
    goalSpriteRoad = new Sprite(renderer, TEXTURE_GOALPOST_ROAD);
    goalSpriteBuilding = new Sprite(renderer, TEXTURE_GOALPOST_BUILDING);

    initHexs({viewRadius-1,viewRadius}, viewRadius);

    MapLoader maploader(state, renderer);
    int mapOffsetX = rand() % (61-2*viewRadius) + viewRadius;
    int mapOffsetY = rand() % (61-2*viewRadius) + viewRadius;
    maploader.load(MAP_0, {mapOffsetX,mapOffsetY}, {viewRadius-1,viewRadius-1}, viewRadius+1);
}

GameWorld::~GameWorld() {
    delete empty;
    delete hover;
    delete goalSprite;
    delete goalSpriteActive;
    delete goalSpriteRoad;
    delete goalSpriteBuilding;

    Sprite::clearTextureCache();
}

Tile* GameWorld::generateRandomTile() {
    int randint = rand() % 5;
    return new Tile(TileType(randint), renderer);
}

void GameWorld::insertHex(SDL_Point coord) {
    hexs.insert(coord);
    //state->setGround(coord, generateRandomTile());
}

void GameWorld::initHexs(SDL_Point origin, int size) {
    hexs.clear();

    int i,x,y1,y2,xfrom,xto;
    xfrom = origin.x-size+((origin.y%2)/2);
    xto = origin.x+size-((origin.y%2)/2);
    for (x=xfrom;x<=xto;++x) {
        insertHex({x, origin.y});
    }
    for (i=0;i<size;++i) {
        y1 = origin.y-i;
        y2 = origin.y+i;
        xfrom = origin.x-size+((i+(origin.y%2))/2);
        xto = origin.x+size-((i+((origin.y+1)%2))/2);
        for (x=xfrom;x<=xto;++x) {
            insertHex({x,y1});
            insertHex({x,y2});
        }
    }

    hexs.begin();
}

void GameWorld::OnClick(SDL_MouseButtonEvent* event) {
    SDL_Point coord = coordsForXY({event->x, event->y});

    if (hexs.find(coord) != hexs.end()) {
        switch (event->button) {
        case SDL_BUTTON_LEFT:
            toolbar->useActiveTool(coord);
            break;
        case SDL_BUTTON_RIGHT:
            toolbar->setActive(ToolType::NONE);
            break;
        default:
            //idle
            break;
        }
    }
}

SDL_Point GameWorld::coordsForXY(SDL_Point ipoint) {
    SDL_Point point;
    point.x = ipoint.x - centeringOffset.x;
    point.y = ipoint.y - centeringOffset.y;
    int gridRowH = hexDims.y*3/4;
    int gridRowTopH = hexDims.y/4;
    int row_odd = (point.y / gridRowH) % 2;
    int row_offset = row_odd * hexDims.x / 2;

    SDL_Point norm;
    norm.x = (point.x - row_offset) % hexDims.x;
    norm.y = point.y % gridRowH;

    SDL_Point ret;

    ret.y = point.y / gridRowH;
    ret.x = (point.x - row_offset) / hexDims.x;

    if (norm.y < gridRowTopH) {
        if (norm.x < hexDims.x / 2) {
            if ((norm.x / hexDims.x) * hexDims.y / 2 <= norm.y) {
                --ret.y;
                ret.x += row_odd-1;
            }
        } else if (norm.x > hexDims.x / 2) {
            if (((hexDims.x-norm.x)/ hexDims.x) * hexDims.y / 2 <= norm.y) {
                --ret.y;
                ret.x += row_odd;
            }
        }
    }

    return ret;
}

void GameWorld::render(SDL_Rect* rect) {
    updateDimensions(rect);

    SDL_SetRenderDrawColor(renderer, 0x09, 0x12, 0x1f, 255);
    SDL_RenderFillRect(renderer, rect);

    for (auto it=hexs.begin();it!=hexs.end();++it) {
        drawHex(*it);
    }

    drawGoals();
    drawAgents();
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

void GameWorld::updateDimensions(SDL_Rect* rect) {
    if (rect->x==winRect.x
            && rect->y==winRect.y
            && rect->w==winRect.w
            && rect->h==winRect.h) {
        return;
    }
    winRect = *rect;
    updateHexDims();

    int hexMapW = hexDims.x*(viewRadius*2-1);
    int hexMapH = hexDims.y*3*(viewRadius*2+1)/4;
    centeringOffset.x = winRect.x + (winRect.w - hexMapW)/2;
    centeringOffset.y = winRect.y + (winRect.h - hexMapH)/2;
}

int GameWorld::dim() {
    return dim_mul*((winRect.h<winRect.w)?winRect.h:winRect.w);
}

void GameWorld::updateHexDims() {
    hexDims = {
        dim()/(3*viewRadius),
        dim()/(4*viewRadius)
    };
}

SDL_Rect GameWorld::getHexRectForCoord(SDL_Point coord) {
    SDL_Rect rect;
    rect.x = centeringOffset.x + (coord.x)*hexDims.x+(coord.y%2)*(hexDims.x/2);
    rect.y = centeringOffset.y + (coord.y*((hexDims.y*3)/4));
    rect.w = hexDims.x;
    rect.h = hexDims.y;
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

void GameWorld::drawGoal(Goal goal, Sprite* sprite) {
    SDL_Rect rect = getHexRectForCoord(goal.data.gotoXY);
    if (sprite == NULL) {
        switch (goal.type) {
            case Goal::GOTO:
                sprite = goalSprite;
                break;
            case Goal::BUILD:
                switch (goal.data.buildType) {
                    case BuildType::ROAD:
                        sprite = goalSpriteRoad;
                        break;
                    case BuildType::HOUSE:
                        sprite = goalSpriteBuilding;
                        break;
                    default:
                        sprite = goalSprite;
                        break;
                }
                break;
            default:
                break;
        }
    }
    if (sprite != NULL && goal.type != Goal::NONE) {
        sprite->render(&rect);
    }
}

void GameWorld::drawGoals() {
    for (auto goal : state->getGoals()) {
        drawGoal(goal);
    }
}

void GameWorld::drawAgents() {
    SDL_Rect rect;
    GOAgent* goagent;
    for (auto agent : state->getAgents()) {
        rect = getHexRectForCoord(agent->getPosition());
        goagent = dynamic_cast<GOAgent*>(agent);
        if (goagent != NULL) {
            drawGoal(goagent->getActiveGoal(), goalSpriteActive);
        }
        agent->render(&rect);
    }
}

void GameWorld::OnLoop() {
    for (auto agent : state->getAgents()) {
        agent->update();
        GoalOrientedAgent* goagent = dynamic_cast<GoalOrientedAgent*>(agent);
        if (goagent!=NULL && !goagent->isBusy()) {
            Goal goal = state->getGoal();
            if (goal.type != Goal::NONE) {
                goagent->addGoal(goal);
            }
        }
    }
}
