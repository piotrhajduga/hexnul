#include <string>
#include "SDL.h"

#include "constants.h"
#include "utils.h"
#include "sprite.h"
#include "thing.h"
#include "road.h"
#include "building.h"

using namespace std;

map<int, Sprite*> BuildingWithLevel::levels;

BuildingWithLevel::BuildingWithLevel(SDL_Renderer* renderer)
: BuildingWithLevel(renderer, 0) {}

BuildingWithLevel::BuildingWithLevel(SDL_Renderer* renderer, int initialLevel)
: RoadNode(renderer) {
    setLevel(initialLevel);
}

BuildingWithLevel::~BuildingWithLevel() {
}

Sprite* BuildingWithLevel::getLevel(int level) {
    Sprite* levelSprite = NULL;

    try {
        LOG(DEBUG, "Looking for building level sprite");
        levelSprite = BuildingWithLevel::levels.at(level);
    } catch (const out_of_range& oor) {
    }

    if (levelSprite==NULL) {
        LOG(INFO, "Building level sprite not found");
        levelSprite = new Sprite(renderer, LEVELS[level].textureFile);
        BuildingWithLevel::levels[level] = levelSprite;
    }

    return levelSprite;
}

void BuildingWithLevel::deleteLevels() {
    for (auto it : levels) {
        delete it.second;
    }
}

int BuildingWithLevel::getLevel() {
    return level;
}

int BuildingWithLevel::incLevel() {
    if (level<MAXLEVEL) { ++level; }
    update();
    return level;
}

void BuildingWithLevel::setLevel(int ilevel) {
    level = ilevel;
    update();
}

void BuildingWithLevel::update() {
    sprite = getLevel(level);
    height = LEVELS[level].height;
}

void BuildingWithLevel::render(SDL_Rect* rect) {
    SDL_Rect textureRect = sprite->getTextureRect();
    SDL_Rect backup = *rect;
    int textureHeight = backup.w * textureRect.h / textureRect.w;
    RoadNode::render(rect);
    if (textureHeight > backup.h) {
        rect->y = backup.y + backup.h - textureHeight;
        rect->h = textureHeight;
    }
    sprite->render(rect);
    rect->y = backup.y;
    rect->h = backup.h;
}

BuildingSegment::BuildingSegment(SDL_Renderer* renderer)
: Sprite(renderer, TEXTURE_BUILDING_SEGMENT), Thing(renderer, BUILDINGSEGMENT_SIZE) {
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
: Sprite(renderer, TEXTURE_BUILDING_SEGMENT), Thing(renderer, BUILDING_SIZE) {
    LOG(DEBUG, "BuildingSegment::BuildingSegment");
}

void Building::render(SDL_Rect* rect) {
    Sprite::render(rect);
};
