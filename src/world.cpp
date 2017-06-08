#include <iostream>

#include "utils.h"
#include "sprite.h"
#include "world.h"

GameWorld::GameWorld(SDL_Renderer *irenderer, GameState *istate) {
    state = istate;
    renderer = irenderer;

    int win_w, win_h;
    SDL_GetRendererOutputSize(renderer, &win_w, &win_h);

    hover = Utils::loadTexture(HOVER_TEXTURE_FILE, renderer);
    SDL_SetTextureBlendMode(hover, SDL_BLENDMODE_ADD);

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
    Sprite::clearTextureCache();
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

void GameWorld::draw() {
    SDL_SetRenderDrawColor(renderer, 0x09, 0x12, 0x1f, 255);
    SDL_RenderClear(renderer);

    for (auto it=hexs.begin();it!=hexs.end();++it) {
        drawHex(*it);
    }

    SDL_RenderPresent(renderer);
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
    bool onHover;
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
        DestR.y -= thing->height;
        DestR.h += thing->height;
    }

    onHover = hoverCoord != NULL && coord == *hoverCoord;
    if (onHover) {
        SDL_RenderCopy(renderer, hover, NULL, &DestR);
    }
}

PointSet GameWorld::getHexs() {
    return hexs;
}
