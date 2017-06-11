#include "SDL.h"

#include "utils.h"
#include "state.h"
#include "sprite.h"
#include "agent.h"

using namespace std;

//TODO: passing AGENT_TEXTURE_FILE from header gives strange errors...
Agent::Agent(SDL_Renderer* renderer, GameState* istate, SDL_Point ipos)
: Sprite(renderer, "assets/world/human.png") {
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

void Agent::move(Direction dir) {
    pos = Utils::getNeighbors(pos)[dir];
}

void Agent::update() {
    LOG(DEBUG, "Agent::update");
}

void Agent::render(SDL_Rect* rect) {
    SDL_Rect newrect = {
        rect->x + rect->w/2 - AGENT_W/2,
        rect->y + rect->h/2 - AGENT_H/2,
        AGENT_W,
        AGENT_H,
    };
    Sprite::render(&newrect);
}

PathNodeCompare::PathNodeCompare(const bool& ireverse) {
    reverse = ireverse;
}

bool PathNodeCompare::operator() (const PathNode& lnode, const PathNode& rnode) const {
    if (reverse) {
        return lnode.g+lnode.h < rnode.g+rnode.h;
    } else {
        return lnode.g+lnode.h > rnode.g+rnode.h;
    }
}

PathfindingAgent::PathfindingAgent(SDL_Renderer* renderer, GameState* state, SDL_Point pos)
: Agent(renderer, state, pos) {
    LOG(DEBUG, "PathfindingAgent::PathfindingAgent");
}

PathfindingAgent::~PathfindingAgent() {}

void PathfindingAgent::setDestination(SDL_Point idest) {
    LOG(DEBUG, "PathfindingAgent::setDestination");
    dest = idest;
    searchPath();
}

void PathfindingAgent::searchPath() {
}

void PathfindingAgent::update() {
    LOG(DEBUG, "PathfindingAgent::update");
    if (!path.empty()) {
        PathNode node = path.front();
        move(node.dir);
        path.pop_front();
    }
}
