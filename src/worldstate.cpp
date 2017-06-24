#include <list>
#include <array>
#include <algorithm>

#include "building.h"
#include "utils.h"
#include "road.h"

#include "worldstate.h"

using namespace std;

WorldState::WorldState() {}
WorldState::~WorldState() {
    for (auto it : ground) {
        delete it.second;
    }
    for (auto it : things) {
        delete it.second;
    }
}

Tile* WorldState::getGround(SDL_Point coord) {
    try {
        return ground.at(coord);
    } catch (const out_of_range& oor) {
        return NULL;
    }
}

void WorldState::setGround(SDL_Point coord, Tile* tile) {
    if (ground[coord] != NULL) {
        LOG(DEBUG, "Ground already present. Remove...");
        delete ground[coord];
    }
    LOG(DEBUG, "Set new ground");
    ground[coord] = tile;
}

bool WorldState::isGround(SDL_Point coord) {
    return ground.find(coord) != ground.end();
}

void WorldState::removeGround(SDL_Point coord) {
    try {
        delete ground.at(coord);
        ground.erase(coord);
    } catch (const out_of_range& oor) {
    }
}

int WorldState::countThings(SDL_Point coord) {
    Thing* thing;
    try {
        thing = things.at(coord);
        if (thing->getType()==STACK) {
            return ((BuildingStack*) thing)->size();
        } else {
            return 1;
        }
    } catch (const out_of_range& oor) {
        return 0;
    }
}

void WorldState::updateNeighbors(SDL_Point icoord, Thing* thing) {
    SDL_Point coord;
    RoadNode* neighbor;
    RoadNode* node = dynamic_cast<RoadNode*>(thing);
    bool cond = node!=NULL && node->isVisible();

    NeighborArray neighbors = Utils::getNeighbors(icoord);

    LOG(DEBUG, "Update neighbors...");
    Direction dir = (Direction)0;
    while (dir<6) {
        coord = neighbors[dir];
        neighbor = dynamic_cast<RoadNode*>(getThing(coord));
        if (neighbor != NULL) {
            neighbor->setSegmentVisible((Direction)((3+dir)%6), cond);
        }
        dir = (Direction) (((int) dir) + 1);
    }
}

void WorldState::updateRoadNode(SDL_Point coord, Thing* thing) {
    RoadNode* neighbor;
    RoadNode* node = dynamic_cast<RoadNode*>(thing);
    if (node == NULL) {
        LOG(DEBUG, "Not a RoadNode");
    }

    NeighborArray neighbors = Utils::getNeighbors(coord);
    Direction dir=(Direction)0;

    LOG(DEBUG, "Update RoadNode");
    while (dir<6) {
        neighbor = dynamic_cast<RoadNode*>(getThing(neighbors[dir]));
        node->setSegmentVisible(dir, neighbor!=NULL && neighbor->isVisible());
        dir = (Direction) (((int) dir) + 1);
    }
}

void WorldState::updateThing(SDL_Point coord, Thing* thing) {
    updateRoadNode(coord, thing);
    updateNeighbors(coord, thing);
}

int WorldState::countNeighborThingType(SDL_Point coord, ThingType type) {
    NeighborArray neighbors = Utils::getNeighbors(coord);
    int count = 0;
    for (auto nb=neighbors.begin();nb!=neighbors.end();++nb) {
        try {
            if (things.at(*nb)->getType()==type) {
                count++;
            }
        } catch (const out_of_range& oor) {
        }
    }
    return count;
}

int WorldState::countNeighborGroundType(SDL_Point coord, TileType type) {
    NeighborArray neighbors = Utils::getNeighbors(coord);
    int count = 0;
    for (auto nb=neighbors.begin();nb!=neighbors.end();++nb) {
        try {
            if (ground.at(*nb)->getType()==type) {
                count++;
            }
        } catch (const out_of_range& oor) {
        }
    }
    return count;
}

void WorldState::putThing(SDL_Point coord, Thing* thing) {
    Thing* currentThing;
    try {
        currentThing = things.at(coord);
        if (currentThing == NULL) {
            things[coord] = thing;
        }
    } catch (const out_of_range& oor) {
        things[coord] = thing;
    }
    updateThing(coord, things[coord]);
}

void WorldState::clearThing(SDL_Point coord) {
    Thing* thing;

    try {
        thing = things.at(coord);
        if (thing!=NULL && thing->getType()==STACK) {
            ((BuildingStack*) thing)->shrink();
            if (((BuildingStack*) thing)->empty()) {
                delete thing;
                thing = NULL;
            }
        } else {
            delete thing;
            thing = NULL;
        }

        if (thing == NULL) {
            things.erase(coord);
        }
    } catch (const out_of_range& oor) {
        thing = NULL;
    }
    updateNeighbors(coord, thing);
}

Thing* WorldState::getThing(SDL_Point coord) {
    try {
        return things.at(coord);
    } catch (const out_of_range& oor) {
        return NULL;
    }
}
