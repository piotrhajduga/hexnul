#include <list>
#include <array>
#include <algorithm>
#include <iostream>
#include <string>

#include "utils.h"

#include "state.h"
#include "thing.h"

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
            return ((ThingStack*) thing)->size();
        } else {
            return 1;
        }
    } catch (const out_of_range& oor) {
        return 0;
    }
}

NeighborArray getNeighbors(SDL_Point coord) {
    int row = coord.y, col=coord.x;
    NeighborArray neighbors = {
        col-1+(row%2), row-1,
        col+(row%2), row-1,
        col-1, row,
        col+1, row,
        col-1+(row%2), row+1,
        col+(row%2), row+1
    };
    return neighbors;
}

int GameState::countNeighborGroundType(SDL_Point coord, TileType type) {
    NeighborArray neighbors = getNeighbors(coord);
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
        if (currentThing!=NULL && currentThing->getType()==STACK) {
            ((ThingStack*) currentThing)->putThing(thing);
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
            delete ((ThingStack*) thing)->takeThing();
        } else {
            delete thing;
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
