#include <list>
#include <array>
#include <algorithm>
#include <iostream>
#include <string>

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
    ground[coord] = tile;
}

bool GameState::isGround(SDL_Point coord) {
    return ground.find(coord) != ground.end();
}

void GameState::removeGround(SDL_Point coord) {
    ground.erase(coord);
}

int GameState::countThings(SDL_Point coord) {
    try {
        return things.at(coord).size();
    } catch (const out_of_range& oor) {
        return 0;
    }
}

NeighborArray getNeighbors(SDL_Point coord) {
    int row = coord.y, col=coord.x;
    NeighborArray neighbors = {
        row-1, col,
        row-1, col+1,
        row, col-1,
        row, col+1,
        row+1, col-1,
        row+1, col
    };
    return neighbors;
}

int GameState::countNeighborGroundType(SDL_Point coord, TileType type) {
    NeighborArray neighbors = getNeighbors(coord);
    int count = 0;
    Tile* tile;
    try {
        for (auto nb=neighbors.begin();nb!=neighbors.end();++nb) {
            tile = ground.at(*nb);
            if (tile != NULL && tile->getType()==type) {
                count++;
            }
        }
    } catch (const out_of_range& oor) {}
    return count;
}

void GameState::putThing(SDL_Point coord, Thing* thing) {
    ThingMap::iterator it = things.find(coord);
    ThingStack thingStack;

    if (it==things.end()) {
        thingStack.push_front(thing);
        things.insert({coord, thingStack});
    } else if (it->second.size() <= MAX_THING_STACK) {
        it->second.push_front(thing);
    }
}

void GameState::clearThing(SDL_Point coord) {
    Thing* thing;

    ThingMap::iterator it = things.find(coord);
    if (it!=things.end() && !it->second.empty()) {
        thing = it->second.front();
        delete thing;
        it->second.pop_front();
    }
}

Thing* GameState::getThing(SDL_Point coord) {
    auto it = things.find(coord);
    if (it!=things.end() && !it->second.empty()) {
        return it->second.front();
    } else return NULL;
}

ThingStack GameState::getThings(SDL_Point coord) {
    return things.find(coord)->second;
}
