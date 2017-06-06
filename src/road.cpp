#include "road.h"

Road::Road(SDL_Renderer* renderer)
    : Thing(renderer) {
    initSegmentSprite(TOPLEFT);
    initSegmentSprite(TOPRIGHT);
    initSegmentSprite(LEFT);
    initSegmentSprite(RIGHT);
    initSegmentSprite(BOTTOMLEFT);
    initSegmentSprite(BOTTOMRIGHT);
}

Road::~Road() {
    for (auto it=segments.begin();it!=segments.end();++it) {
        if (it->second.sprite != NULL) {
            delete it->second.sprite;
        }
    }
}

void Road::setVisible(RoadDir dir) {
    segments[dir].isVisible = true;
}

void Road::render(SDL_Rect* rect) {
    for (auto it=segments.begin();it!=segments.end();++it) {
        if (it->second.isVisible) {
            it->second.sprite->render(rect);
        }
    }
}

void Road::initSegmentSprite(RoadDir dir) {
    segments[dir].sprite = new Sprite(renderer, Road::SEGMENTS[dir]);
}
