#include "road.h"

Road::Road(SDL_Renderer* renderer)
: Thing(renderer) {
    center = new Sprite(renderer, CENTER);
    for (int i=0;i<6;++i) {
        segments[Direction(i)].sprite = new Sprite(renderer, Road::SEGMENTS[Direction(i)]);
    }
}

Road::~Road() {
    for (auto it : segments) {
        if (it.second.sprite != NULL) {
            delete it.second.sprite;
        }
    }
    delete center;
}

void Road::setSegmentVisible(Direction dir) {
    setSegmentVisible(dir, true);
}

void Road::setSegmentVisible(Direction dir, bool cond) {
    segments[dir].isVisible = cond;
}

void Road::render(SDL_Rect* rect) {
    bool noneVisible = true;
    for (auto it : segments) {
        if (it.second.isVisible) {
            noneVisible = false;
            it.second.sprite->render(rect);
        }
    }
    if (noneVisible) {
        center->render(rect);
    }
}
