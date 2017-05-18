#include "hexnul.h"

/**
 * initial goal is to draw
 * HEX grid - a grid of hexagonal tiles
 * and have actors walk from point A to point B
 * only allowed moves are to adjacent free tiles
 *
 * free means that no other object can occupy that tile
 *
 * remember about the coordinate system
 *
 * and have fun!
 */

int main(int argc, char* argv[]) {
    HexNullApp app;
    return app.OnExecute();
}

HexNullApp::HexNullApp() {
    display = NULL;
    running = false;
}

int HexNullApp::OnExecute() {
    running = true;

    if (OnInit() == false) {
        return -1;
    }

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }
    OnCleanup();
    return 0;
}

bool HexNullApp::OnInit() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        return false;
    }

    display = SDL_CreateWindow("0x0",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WIN_W, WIN_H, SDL_WINDOW_OPENGL);

    if(display == NULL) {
        return false;
    }
    renderer = SDL_CreateRenderer(display, -1, 0);
    if(renderer == NULL) {
        return false;
    }
    SDL_RenderSetLogicalSize(renderer, WIN_W, WIN_H);

    return true;
}

void HexNullApp::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT: running = false;
                       break;
        default: break;
    }
}

void HexNullApp::OnLoop() {
}

void HexNullApp::OnRender() {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(renderer);

    drawHexs((WIN_H/RECT_H)-1, (WIN_W/RECT_W)-1);

    SDL_RenderPresent(renderer);
}

void HexNullApp::drawHexs(int rows, int cols) {
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 255);
    SDL_Rect rect;

    for (int row=0;row<rows;row++) {
        for (int col=0;col<cols;col++) {
            rect.x = BOARD_OFFSET_X + (RECT_W * col) + (RECT_W_OFFSET * (row%2));
            rect.y = BOARD_OFFSET_Y + RECT_H * (row);
            rect.w = RECT_W;
            rect.h = RECT_H;

            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void HexNullApp::OnCleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(display);

    SDL_Quit();
}
