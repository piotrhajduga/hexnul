#include <list>
#include <array>
#include <algorithm>

#include "building.h"
#include "utils.h"

#include "state.h"

using namespace std;

GameState::GameState() {}
GameState::~GameState() {}

Tile* GameState::getGround(SDL_Point coord) {
    try {
        return ground.at(coord);
    } catch (const out_of_range& oor) {
        return NULL;
    }
}

void GameState::setGround(SDL_Point coord, Tile* tile) {
    if (ground[coord] != NULL) {
        LOG(DEBUG, "Ground already present. Remove...");
        delete ground[coord];
    }
    LOG(DEBUG, "Set new ground");
    ground[coord] = tile;
}

bool GameState::isGround(SDL_Point coord) {
    return ground.find(coord) != ground.end();
}

void GameState::removeGround(SDL_Point coord) {
    ground.erase(coord);
}

int GameState::countThings(SDL_Point coord) {
    Thing* thing;
    try {
        thing = things.at(coord);
        if (thing->getType()==STACK) {
            return ((BuildingStack*) thing)->size();
        } else {
            return 1;
        }
    } catch (const out_of_range& oor) {
        return 0;
    }
}

int GameState::countNeighborThingType(SDL_Point coord, ThingType type) {
    NeighborArray neighbors = Utils::getNeighbors(coord);
    int count = 0;
    for (auto nb=neighbors.begin();nb!=neighbors.end();++nb) {
        try {
            if (things.at(*nb)->getType()==type) {
                count++;
            }
        } catch (const out_of_range& oor) {
        }
    }
    return count;
}

int GameState::countNeighborGroundType(SDL_Point coord, TileType type) {
    NeighborArray neighbors = Utils::getNeighbors(coord);
    int count = 0;
    for (auto nb=neighbors.begin();nb!=neighbors.end();++nb) {
        try {
            if (ground.at(*nb)->getType()==type) {
                count++;
            }
        } catch (const out_of_range& oor) {
        }
    }
    return count;
}

void GameState::putThing(SDL_Point coord, Thing* thing) {
    Thing* currentThing;
    try {
        currentThing = things.at(coord);
        if (currentThing == NULL) {
            things[coord] = thing;
        }
    } catch (const out_of_range& oor) {
        things[coord] = thing;
    }
}

void GameState::clearThing(SDL_Point coord) {
    Thing* thing;

    try {
        thing = things.at(coord);
        if (thing!=NULL && thing->getType()==STACK) {
            ((BuildingStack*) thing)->shrink();
            if (((BuildingStack*) thing)->empty()) {
                delete thing;
                thing = NULL;
            }
        } else {
            delete thing;
            thing = NULL;
        }

        if (thing == NULL) {
            things.erase(coord);
        }
    } catch (const out_of_range& oor) {
    }
}

Thing* GameState::getThing(SDL_Point coord) {
    try {
        return things.at(coord);
    } catch (const out_of_range& oor) {
        return NULL;
    }
}
