#include "utils.h"

#include "sprite.h"

#include "road.h"

RoadNode::RoadNode(SDL_Renderer* renderer)
: Thing(renderer) {
    for (int i=0;i<6;++i) {
        segments[Direction(i)].sprite = new Sprite(renderer, SEGMENTS[Direction(i)]);
    }
}

RoadNode::~RoadNode() {
    for (auto it : segments) {
        if (it.second.sprite != NULL) {
            delete it.second.sprite;
        }
    }
}

void RoadNode::render(SDL_Rect* rect) {
    for (auto it : segments) {
        if (it.second.isVisible) {
            it.second.sprite->render(rect);
        }
    }
}

void RoadNode::setSegmentVisible(Direction dir) {
    setSegmentVisible(dir, true);
}

void RoadNode::setSegmentVisible(Direction dir, bool cond) {
    if (!segments[dir].isVisible && cond) {
        visibleCount++;
    } else if (segments[dir].isVisible && !cond) {
        visibleCount--;
    }
    segments[dir].isVisible = cond;
}

int RoadNode::getVisibleCount() {
    return visibleCount;
}

bool RoadNode::isVisible() {
    return true;
}

Road::Road(SDL_Renderer* renderer)
: RoadNode(renderer), Sprite(renderer, TEXTURE_ROAD_CENTER) {}

void Road::render(SDL_Rect* rect) {
    RoadNode::render(rect);
    if (getVisibleCount()<2) {
        Sprite::render(rect);
    }
}
