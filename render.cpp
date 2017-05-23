#include "render.h"

GameRender::GameRender(SDL_Renderer* renderer, GameState* state) {
    this->renderer = renderer;
    this->state = state;
}

GameRender::~GameRender() {}

void GameRender::render() {
    int win_w, win_h;

    SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 255);
    SDL_RenderClear(renderer);

    SDL_GetRendererOutputSize(renderer, &win_w, &win_h);
    int cols = (win_w)/HEX_W;
    int rows = (win_h)/((HEX_H*3)/4);
    drawHexs(cols,rows);

    SDL_RenderPresent(renderer);
}

void GameRender::drawHexs(int cols, int rows) {
    for (int x=0;x<cols;x++) {
        for (int y=0;y<rows;y++) {
            drawHex(x, y);
        }
    }
}

void GameRender::drawHex(int col, int row) {
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
}


