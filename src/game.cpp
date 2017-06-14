#include <iostream>
#include <algorithm>

#include "utils.h"

#include "road.h"
#include "game.h"

using namespace std;

Game::Game() {
    display = NULL;
    running = false;
}

int Game::OnExecute() {
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

bool Game::OnInit() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        return false;
    }

    display = SDL_CreateWindow("0x0",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WIN_W, WIN_H, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    if(display == NULL) {
        return false;
    }
    renderer = SDL_CreateRenderer(display, -1, 0);
    if(renderer == NULL) {
        return false;
    }
    SDL_RenderSetLogicalSize(renderer, WIN_W, WIN_H);

    toolbar = new Toolbar(renderer, &state);
    world = new GameWorld(renderer, &state, toolbar);

    return true;
}

void Game::OnEvent(SDL_Event* event) {
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

void Game::OnMouseMove(SDL_MouseMotionEvent* event) {
    if ((event->y) <= WIN_H-TOOLBAR_H) {
        toolbar->setHover(ToolType::NONE);
        world->OnMouseMove(event);
    } else {
        toolbar->OnMouseMove(event);
    }
}

void Game::OnClick(SDL_MouseButtonEvent* event) {
    if (event->y <= WIN_H-TOOLBAR_H) {
        world->OnClick(event);
    } else {
        toolbar->OnClick(event);
    }
}

void Game::OnLoop() {
    world->OnLoop();
}

void Game::OnRender() {
    SDL_Rect rect;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 255);
    SDL_RenderClear(renderer);

    rect = {0, 0, WIN_W, WIN_H-TOOLBAR_H};
    world->render(&rect);

    rect = {0, WIN_H-TOOLBAR_H, WIN_W, TOOLBAR_H};
    toolbar->render(&rect);

    SDL_RenderPresent(renderer);
}

void Game::OnCleanup() {
    delete toolbar;
    delete world;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(display);

    SDL_Quit();
}
