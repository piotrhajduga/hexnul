#include "state.h"
#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

void printSet(std::string name, GameState::PointSet points) {
    std::cout<<name<<" = {";
    for (auto it=points.begin();it!=points.end();++it) {
        std::cout<<"("<<it->x<<","<<it->y<<")";
    }
    std::cout<<"}"<<std::endl;
}

GameState::GameState() {
    hexs.begin();
}
GameState::~GameState() {}

void GameState::toggleGround(SDL_Point point) {
    if (hexs.find(point) != hexs.end()) {
        if (ground.find(point) == ground.end()) {
            ground.insert(point);
        } else {
            ground.erase(point);
        }
    }
}

bool GameState::isGround(SDL_Point coord) {
    return ground.find(coord) != ground.end();
}

int GameState::countNeighbourGround(SDL_Point coord) {
    int count = 0;
    GameState::PointSet neighbours = {
        {coord.x-1+(coord.y%2),coord.y-1},{coord.x+(coord.y%2),coord.y-1},
        {coord.x-1,coord.y},{coord.x+1,coord.y},
        {coord.x-1+(coord.y%2),coord.y+1},{coord.x+(coord.y%2),coord.y+1},
    };

    for (auto it=neighbours.begin();it!=neighbours.end();++it) {
        if (isGround(*it) && getThing(*it)==NULL) ++count;
    }

    return count;
}

GameState::PointSet GameState::getHexs() {
    return hexs;
}

void GameState::putThing(SDL_Point coord, Thing* thing) {
    things.insert({coord, thing});
}
void GameState::clearThing(SDL_Point coord) {
    things.erase(coord);
}
Thing* GameState::getThing(SDL_Point coord) {
    auto it = things.find(coord);
    return (it==things.end())?NULL:it->second;
}
