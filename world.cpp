#include "world.h"
//#include <iostream>

GameWorld::GameWorld(SDL_Renderer *irenderer) {
    renderer = irenderer;

    int win_w, win_h;
    SDL_GetRendererOutputSize(renderer, &win_w, &win_h);

    int cols = win_w / HEX_W;
    int rows = win_h / ((HEX_H*3)/4);
    for (int i=0;i<cols;i++) {
        for (int j=0;j<rows;j++) {
            hexs.insert({i,j});
        }
    }
}

GameWorld::~GameWorld() {
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

    //std::cout<<"col="<<col<<",row="<<row<<std::endl;

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
}


