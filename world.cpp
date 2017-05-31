#include "world.h"
#include <iostream>

GameWorld::GameWorld(SDL_Renderer *irenderer, GameState *istate) {
    state = istate;
    renderer = irenderer;

    int win_w, win_h;
    SDL_GetRendererOutputSize(renderer, &win_w, &win_h);

    greenTile = loadTexture("green.png");
    redTile = loadTexture("red.png");
    blueTile = loadTexture("blue.png");
}

GameWorld::~GameWorld() {
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
    auto hexs = state->getHexs();

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

    SDL_SetRenderDrawColor(renderer, 0xc4, 0xe0, 0xf2, 255);
    SDL_Point points[POINTS_COUNT] = {
        {x-(HEX_W/2), y-(HEX_H/4)},
        {x          , y-(HEX_H/2)},
        {x+(HEX_W/2), y-(HEX_H/4)},
        {x+(HEX_W/2), y+(HEX_H/4)},
        {x          , y+(HEX_H/2)},
        {x-(HEX_W/2), y+(HEX_H/4)},
        {x-(HEX_W/2), y-(HEX_H/4)}
    };

    SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
}

SDL_Texture* GameWorld::loadTexture(const char *file) {
    SDL_Surface* loadingSurface = IMG_Load(file);
    if (loadingSurface == NULL) {
        std::cout<<"Cannot load "<<file<<std::endl;
        return NULL;
    }
    SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    return tx;
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
    SDL_Texture* tx = NULL;
    Thing* thing = NULL;

    DestR.x = (coord.x)*HEX_W+(coord.y%2)*(HEX_W/2);
    DestR.y = (coord.y*((HEX_H*3)/4));
    DestR.w = HEX_W;
    DestR.h = HEX_H;

    if (state->isGround(coord)) {
        tx = greenTile;
        SDL_RenderCopy(renderer, tx, NULL, &DestR);
    }

    drawHexOutline(coord);

    thing = state->getThing(coord);
    if (thing != NULL) {
        thing->render(&DestR);
    }

    onHover = hoverCoord != NULL && coord == *hoverCoord;
    if (onHover) {
        if (state->getThing(coord)==NULL) {
            tx = blueTile;
        } else {
            tx = redTile;
        }
        SDL_RenderCopy(renderer, tx, NULL, &DestR);
    }
}
