#include <string>

#include "SDL.h"
#include "sprite.h"
#include "thing.h"
#include "utils.h"

#include "building.h"

using namespace std;

BuildingSegment::BuildingSegment(SDL_Renderer* renderer)
: Sprite(renderer, BUILDING_TEXTURE_FILE), Thing(renderer, BUILDING_SIZE) {
    LOG(DEBUG, "BuildingSegment::BuildingSegment");
}

void BuildingSegment::render(SDL_Rect* rect) {
    Sprite::render(rect);
};

Building::Building(SDL_Renderer* renderer)
: Thing(renderer, 0) {
    LOG(DEBUG, "Building::Building");
}

void Building::grow() {
    if (size() >= MAX_SEGMENTS) return;
    LOG(DEBUG, "Building::grow");
    auto segment = new BuildingSegment(renderer);
    height += segment->height;
    push_front(segment);
}

void Building::shrink() {
    LOG(DEBUG, "Building::shrink");
    auto segment = front();
    height -= segment->height;
    delete segment;
    pop_front();
}

void Building::render(SDL_Rect* rect) {
    SDL_Rect DestR = *rect;
    for (auto it : *this) {
        it->render(&DestR);
        DestR.y-=it->height;
    }
}
