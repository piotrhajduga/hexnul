#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

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
    cout<<"Removing ("<<coord.x<<","<<coord.y<<")"<<endl;
    ground.erase(coord);
}

int GameState::countThings(SDL_Point coord) {
    try {
        return things.at(coord).size();
    } catch (const out_of_range& oor) {
        return 0;
    }
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
