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
    for (auto it : segments) {
        if (it.second.sprite != NULL) {
            delete it.second.sprite;
        }
    }
}

void Road::setVisible(Direction dir) {
    setVisible(dir, true);
}

void Road::setVisible(Direction dir, bool cond) {
    segments[dir].isVisible = cond;
}

void Road::render(SDL_Rect* rect) {
    for (auto it : segments) {
        if (it.second.isVisible) {
            it.second.sprite->render(rect);
        }
    }
}

void Road::initSegmentSprite(Direction dir) {
    segments[dir].sprite = new Sprite(renderer, Road::SEGMENTS[dir]);
}
