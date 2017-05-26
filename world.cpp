#include "world.h"
//#include <iostream>

GameWorld::GameWorld(SDL_Renderer *irenderer) {
    renderer = irenderer;

    int win_w, win_h;
    SDL_GetRendererOutputSize(renderer, &win_w, &win_h);

    SDL_Point myPoints[] = {
        {0, 0},
        {1, 1},
        {0, 1},
        {1, 0},
        {1, 4},
        {0, 2},
        {2, 2},
        {2, 4},
        {3, 4},
        {3, 3},
        {3, 2},
        {7, 0},
        {9, 3},
        {8, 3},
        {9, 2},
        {9, 6},
        {8, 4},
        {9, 4},
        {8, 6},
        {7, 6},
        {7, 5}
    };
    hexs.insert(myPoints, myPoints+20);
}

GameWorld::~GameWorld() {
}

SDL_Point GameWorld::coordsForXY(SDL_Point point) {
    SDL_Point ret;

    ret.x = point.x / HEX_W;
    ret.y = point.y / ((HEX_H*3)/4);

    return ret;
}

void GameWorld::setActive(SDL_Point point) {
    activePoints.insert(point);
}

void GameWorld::setInactive(SDL_Point point) {
    activePoints.erase(point);
}

void GameWorld::draw() {
    SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 255);
    SDL_RenderClear(renderer);

    for (auto it=hexs.begin();it!=hexs.end();++it) {
        drawHex(it->x, it->y);
    }

    SDL_RenderPresent(renderer);
}

void GameWorld::drawHex(int col, int row) {
    const int POINTS_COUNT = 7;
    int x = (HEX_W/2) + (col)*HEX_W+(row%2)*(HEX_W/2);
    int y = (HEX_H/2) + (row*((HEX_H*3)/4));

    SDL_SetRenderDrawColor(renderer, 0x04, 0x10, 0x02, 255);
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

    if (activePoints.find({col, row}) != activePoints.end()) {
        //std::cout<<"found!"<<std::endl;
        SDL_Rect rect;
        rect.x = x-4;
        rect.y = y-4;
        rect.w = 8;
        rect.h = 8;
        SDL_RenderFillRect(renderer, &rect);
    }
}


