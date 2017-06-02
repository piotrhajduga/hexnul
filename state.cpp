#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

#include "state.h"

using namespace std;

void printSet(string name, GameState::PointSet points) {
    cout<<name<<" = {";
    for (auto it=points.begin();it!=points.end();++it) {
        cout<<"("<<it->x<<","<<it->y<<")";
    }
    cout<<"}"<<endl;
}

GameState::GameState() {}
GameState::~GameState() {}

void GameState::toggleGround(SDL_Point point) {
    if (ground.find(point) == ground.end()) {
        ground.insert(point);
    } else {
        ground.erase(point);
    }
}

bool GameState::isGround(SDL_Point coord) {
    return ground.find(coord) != ground.end();
}

bool GameState::canPutThing(SDL_Point coord) {
    GameState::PointSet neighbours = {
        {coord.x-1+(coord.y%2),coord.y-1},{coord.x+(coord.y%2),coord.y-1},
        {coord.x-1,coord.y},{coord.x+1,coord.y},
        {coord.x-1+(coord.y%2),coord.y+1},{coord.x+(coord.y%2),coord.y+1},
    };

    for (auto it=neighbours.begin();it!=neighbours.end();++it) {
        //TODO: logic!
    }

    return true;
}

int GameState::countThings(SDL_Point coord) {
    ThingMap::iterator it = things.find(coord);
    if (it != things.end()) {
        return it->second.size();
    }
    else return 0;
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

GameState::ThingStack GameState::getThings(SDL_Point coord) {
    return things.find(coord)->second;
}
