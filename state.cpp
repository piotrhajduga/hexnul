#include "state.h"
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

void GameState::toggleActive(SDL_Point point) {
    if (hexs.find(point) != hexs.end()) {
        if (activePoints.find(point) == activePoints.end()) {
            activePoints.insert(point);
        } else {
            activePoints.erase(point);
        }
    }
}

bool GameState::isActive(SDL_Point point) {
    return activePoints.find(point) != activePoints.end();
}

GameState::PointSet GameState::getHexs() {
    return hexs;
}
