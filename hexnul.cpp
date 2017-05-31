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

HexNullApp::HexNullApp() {
    display = NULL;
    running = false;
}

int HexNullApp::OnExecute() {
    const int milisPerFrame = (1000/FPS);
    running = true;

    if (OnInit() == false) {
        return -1;
    }

    SDL_Event event;

    while (running) {
        ticks = SDL_GetTicks();
        OnRender();
        OnLoop();
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }
        int passed = SDL_GetTicks()-ticks;
        if (passed<milisPerFrame) {
            SDL_Delay(milisPerFrame-passed);
        }
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

    world = new GameWorld(renderer, &state);

    return true;
}

void HexNullApp::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            OnMouseMove((SDL_MouseMotionEvent*) event);
            break;
        case SDL_MOUSEBUTTONUP:
            OnClick((SDL_MouseButtonEvent*) event);
            break;
        case SDL_QUIT:
            running = false;
            break;
        default: break;
    }
}

void HexNullApp::OnMouseMove(SDL_MouseMotionEvent* event) {
    SDL_Point coords = world->coordsForXY({event->x, event->y});
    world->setHover(coords);
}

void HexNullApp::OnClick(SDL_MouseButtonEvent* event) {
    SDL_Point coords = world->coordsForXY({event->x, event->y});
    if (state.isGround(coords)) {
        if (state.getThing(coords)==NULL) {
            if (state.countNeighbourGround(coords)>0) {
                state.putThing(coords, new Thing(renderer));
            }
        } else {
            state.clearThing(coords);
        }
    } else {
        state.toggleGround(coords);
    }
}

void HexNullApp::OnLoop() {
}

void HexNullApp::OnRender() {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 255);
    SDL_RenderClear(renderer);

    world->draw();
}

void HexNullApp::OnCleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(display);

    SDL_Quit();
}
