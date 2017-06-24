#include <set>
#include <map>
#include <queue>

#include "SDL.h"
#include "constants.h"

#include "utils.h"
#include "worldstate.h"
#include "tile.h"
#include "thing.h"
#include "sprite.h"
#include "building.h"
#include "pathnode.h"
#include "agent.h"

using namespace std;

//TODO: passing AGENT_TEXTURE_FILE from header gives strange errors...
Agent::Agent(SDL_Renderer* renderer, WorldState* istate, SDL_Point ipos)
: Sprite(renderer, TEXTURE_AGENT) {
    state = istate;
    pos = ipos;
}

Agent::~Agent() {}

void Agent::setPosition(SDL_Point ipos) {
    pos = ipos;
}

SDL_Point Agent::getPosition() {
    return pos;
}

void Agent::move(SDL_Point coord) {
    pos = coord;
}

Uint8 Agent::getSpeed() {
    return speed;
}

void Agent::setSpeed(Uint8 ispeed) {
    speed = ispeed;
}

void Agent::move(Direction dir) {
    pos = Utils::getNeighbors(pos)[dir];
}

void Agent::update() {
    LOG(DEBUG, "Agent::update");
}

void Agent::render(SDL_Rect* rect) {
    SDL_Rect newrect = {
        rect->x + rect->w/2 - AGENT_W/2,
        rect->y + rect->h/2 - AGENT_H*3/4,
        AGENT_W,
        AGENT_H,
    };
    Sprite::render(&newrect);
}

PathfindingAgent::PathfindingAgent(SDL_Renderer* renderer, WorldState* state, SDL_Point pos)
: Agent(renderer, state, pos) {
    LOG(DEBUG, "PathfindingAgent::PathfindingAgent");
}

PathfindingAgent::~PathfindingAgent() {}

void PathfindingAgent::setDestination(SDL_Point idest) {
    LOG(DEBUG, "PathfindingAgent::setDestination");
    dest = idest;
    findPath();
    lastMoveTicks = SDL_GetTicks();
}

bool PathfindingAgent::isPassable(SDL_Point coord) {
    PathNode* tileNode = state->getGround(coord);
    PathNode* thingNode = state->getThing(coord);

    return (tileNode!=NULL && tileNode->isPassable())
        && (thingNode==NULL || thingNode->isPassable());
}

int PathfindingAgent::gscore(SDL_Point coord) {
    int cost = 0;

    PathNode* tileNode = state->getGround(coord);
    cost += tileNode->getMoveCost();

    PathNode* thingNode = state->getThing(coord);
    cost = (thingNode==NULL)?cost:thingNode->getMoveCost();

    return cost;
}

int PathfindingAgent::hscore(SDL_Point point) {
    return abs(dest.x-point.x)+abs(dest.y-point.y);
}

bool PathfindingAgent::findPath() {
    SDL_Point node;

    map<SDL_Point, int, compareCoords> g;
    map<SDL_Point, int, compareCoords> h;

    map<SDL_Point, SDL_Point, compareCoords> cameFrom;

    set<SDL_Point, compareCoords> closed;
    set<SDL_Point, compareCoords> open;

    auto compareCoordPriorities = [&] (const SDL_Point& lp, const SDL_Point& rp) {
        return g[lp]+h[lp] > g[rp]+h[rp];
    };
    priority_queue<SDL_Point,vector<SDL_Point>,decltype(compareCoordPriorities)> openqueue(compareCoordPriorities);

    g[pos] = gscore(pos);
    h[pos] = hscore(pos);

    cameFrom[pos] = pos;

    open.insert(pos);
    openqueue.push(pos);

    while (!open.empty()) {
        node = openqueue.top();
        openqueue.pop();
        open.erase(node);

        if (equalsCoords()(node, dest)) {
            LOG(DEBUG, "Found target!");
            path.clear();
            node = dest;
            do {
                path.push_front(node);
                node = cameFrom[node];
            } while (cameFrom.find(node)!=cameFrom.end()
                    && !equalsCoords()(cameFrom[node], node));

            return true;
        }
        closed.insert(node);

        for (SDL_Point coord : Utils::getNeighbors(node)) {
            if (closed.find(coord)!=closed.end()) {
                continue;
            }
            if (!isPassable(coord)) {
                continue;
            }
            int tmp_g = g[node] + gscore(coord);
            
            if (open.find(coord) == open.end()) {
                cameFrom[coord] = node;

                g[coord] = tmp_g;
                h[coord] = hscore(coord);

                open.insert(coord);
                openqueue.push(coord);
            } else if (tmp_g < g[coord]) {
                cameFrom[coord] = node;
                g[coord] = tmp_g;
            }
        }
    }

    return false;

}

void PathfindingAgent::update() {
    if (!path.empty()) {
        if (lastMoveTicks == 0 || SDL_TICKS_PASSED(SDL_GetTicks(), lastMoveTicks+gscore(pos)*30-getSpeed())) {
            LOG(DEBUG, string("Agent pos: {")+to_string(pos.x)+","+to_string(pos.y)+"}");
            LOG(DEBUG, string("Agent gscore: ")+to_string(gscore(pos)));
            LOG(DEBUG, string("Agent hscore: ")+to_string(hscore(pos)));
            SDL_Point node = path.front();
            path.pop_front();
            move(node);
            lastMoveTicks = SDL_GetTicks();
        }
    }
}

GoalOrientedAgent::GoalOrientedAgent(SDL_Renderer* renderer, WorldState* state, SDL_Point position)
: PathfindingAgent(renderer, state, position) {
    resetGoal();
}

GoalOrientedAgent::~GoalOrientedAgent() {}

void GoalOrientedAgent::setActiveGoal() {
    if (!goals.empty()) {
        activeGoal = goals.top();
        goals.pop();
    //} else {
        //Wandering agent
        //int dxy = 2-(rand() % 5);
        //activeGoal.type = Goal::GOTO;
        //TODO:gotoXY limiting
        //activeGoal.data.gotoXY = {pos.x+dxy,pos.y+dxy};
        //goals.push(activeGoal);
    }
}

void GoalOrientedAgent::resetGoal() {
    activeGoal = {Goal::NONE, 1, 0};
}

void GoalOrientedAgent::actionGOTO(SDL_Point gotoxy) {
    if (equalsCoords()(pos, gotoxy)) {
        resetGoal();
    } else if (path.empty()) {
        setDestination(gotoxy);
    } else {
        PathfindingAgent::update();
    }
}

void GoalOrientedAgent::actionBUILD(SDL_Point gotoxy) {
    Thing* thing = state->getThing(gotoxy);
    if (thing == NULL) {
        actionGOTO(gotoxy);
        if (equalsCoords()(pos, gotoxy)) {
            switch (activeGoal.data.buildType) {
                case BuildType::HOUSE:
                    thing = new BuildingWithLevel(renderer);
                    break;
                case BuildType::ROAD:
                    thing = new Road(renderer);
                    break;
            }
            if (thing != NULL) {
                state->putThing(gotoxy, thing);
            }
            resetGoal();
        }
    } else {
        BuildingWithLevel* building = dynamic_cast<BuildingWithLevel*>(thing);
        if (building!=NULL) {
            actionGOTO(gotoxy);
            if (equalsCoords()(pos, gotoxy)) {
                building->incLevel();
                state->updateThing(pos, building);
                resetGoal();
            }
        } else {
            resetGoal();
        }
    }
}

void GoalOrientedAgent::update() {
    switch (activeGoal.type) {
        case Goal::GOTO:
            actionGOTO(activeGoal.data.gotoXY);
            break;
        case Goal::BUILD:
            actionBUILD(activeGoal.data.gotoXY);
            break;
        case Goal::NONE:
            setActiveGoal();
            break;
        default:
            break;
    }
}

bool GoalOrientedAgent::isBusy() {
    return activeGoal.type != Goal::NONE;
}

void GoalOrientedAgent::addGoal(Goal goal) {
    LOG(DEBUG, "add GOAgent Goal");
    goals.push(goal);
}
