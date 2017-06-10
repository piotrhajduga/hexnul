#include <string>

#include "SDL.h"
#include "sprite.h"
#include "thing.h"
#include "utils.h"

#include "building.h"

using namespace std;

BuildingSegment::BuildingSegment(SDL_Renderer* renderer)
: Sprite(renderer, BUILDINGSEGMENT_TEXTURE_FILE), Thing(renderer, BUILDINGSEGMENT_SIZE) {
    LOG(DEBUG, "BuildingSegment::BuildingSegment");
}

void BuildingSegment::render(SDL_Rect* rect) {
    Sprite::render(rect);
};

BuildingStack::BuildingStack(SDL_Renderer* renderer)
: Thing(renderer, 0) {
    LOG(DEBUG, "Building::Building");
}

void BuildingStack::grow() {
    if (size() >= MAX_SEGMENTS) return;
    LOG(DEBUG, "Building::grow");
    auto segment = new BuildingSegment(renderer);
    height += segment->height;
    push_front(segment);
}

void BuildingStack::shrink() {
    LOG(DEBUG, "Building::shrink");
    auto segment = front();
    height -= segment->height;
    delete segment;
    pop_front();
}

void BuildingStack::render(SDL_Rect* rect) {
    SDL_Rect DestR = *rect;
    for (auto it : *this) {
        it->render(&DestR);
        DestR.y-=it->height;
    }
}

Building::Building(SDL_Renderer* renderer)
: Sprite(renderer, BUILDING_TEXTURE_FILES[0]), Thing(renderer, BUILDING_SIZE) {
    LOG(DEBUG, "BuildingSegment::BuildingSegment");
}

void Building::render(SDL_Rect* rect) {
    Sprite::render(rect);
};
