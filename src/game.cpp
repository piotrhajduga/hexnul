#include <iostream>
#include <algorithm>

#include "utils.h"

#include "thing.h"
#include "direction.h"
#include "road.h"
#include "game.h"

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

    world = new GameWorld(renderer, &state);
    tileFactory = new TileFactory(renderer);
    thingFactory = new ThingFactory(renderer);

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
    SDL_Point coords = world->coordsForXY({event->x, event->y});
    world->setHover(coords);
}

Road* Game::createRoad(NeighborArray neighbors) {
    LOG(DEBUG, "Create Road");
    Road* road = new Road(renderer);

    updateRoad(road, neighbors);

    return road;
}

void Game::updateRoad(Road* road, NeighborArray neighbors) {
    Thing* neighbor;
    Direction dir=(Direction)0;

    LOG(DEBUG, "Update Road");

    while (dir<6) {
        neighbor = state.getThing(neighbors[dir]);
        road->setSegmentVisible(dir, neighbor!=NULL);
        dir = (Direction) (((int) dir) + 1);
    }
}

void Game::updateNeighbors(NeighborArray neighbors, Thing* thing) {
    Thing* neighbor;
    SDL_Point coord;
    Direction dir = (Direction)0;

    LOG(DEBUG, "Update neighbors");

    while (dir<6) {
        coord = neighbors[dir];
        neighbor = state.getThing(coord);
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

void Game::OnClick(SDL_MouseButtonEvent* event) {
    SDL_Point coords = world->coordsForXY({event->x, event->y});
    Tile* ground = NULL;
    Thing* thing = state.getThing(coords);
    int neighborCount;
    NeighborArray neighbors = Utils::getNeighbors(coords);

    if (world->getHexs().find(coords) != world->getHexs().end()) {
        switch (event->button) {
        case SDL_BUTTON_LEFT:
            ground = state.getGround(coords);
            if (ground != NULL) {
                if (ground->canPutThing()) {
                    if (thing == NULL) {
                        if ((state.countNeighborThingType(coords, STACK) > 1
                            || state.countNeighborThingType(coords, ROAD) > 0)
                            && state.countNeighborThingType(coords, ROAD) < 3
                            ) {
                            thing = createRoad(neighbors);
                        } else {
                            LOG(DEBUG, "Create ThingStack");
                            thing = thingFactory->create(STACK);
                        }
                        state.putThing(coords, thing);
                    }

                    if(thing->getType()==STACK) {
                        LOG(DEBUG, "Create BuildingSegment");
                        ((ThingStack*) thing)->putThing(thingFactory->create(BUILDING));
                    }
                } else {
                    if (ground->getType()==GRASS) {
                        neighborCount = state.countNeighborGroundType(coords, WATER);
                        if (neighborCount>1) {
                            state.setGround(coords, tileFactory->create(SAND));
                        } else {
                            state.setGround(coords, tileFactory->create(DIRT));
                        }
                    }
                }
            } else {
                state.setGround(coords, tileFactory->create(GRASS));
            }
            break;
        case SDL_BUTTON_RIGHT:
            ground = state.getGround(coords);

            if (state.countThings(coords) > 0) {
                state.clearThing(coords);
                thing = state.getThing(coords);
            } else if (ground != NULL) {
                state.removeGround(coords);
            } else {
                state.setGround(coords, tileFactory->create(WATER));
            }
            break;
        default:
            //idle
            break;
        }
    }

    updateNeighbors(neighbors, thing);
}

void Game::OnLoop() {
}

void Game::OnRender() {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 255);
    SDL_RenderClear(renderer);

    world->draw();
}

void Game::OnCleanup() {
    delete tileFactory;
    delete thingFactory;
    delete world;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(display);

    SDL_Quit();
}
