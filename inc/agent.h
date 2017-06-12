#ifndef	_HEXNUL_AGENT_H_
#define	_HEXNUL_AGENT_H_

#include <list>
#include <queue>
#include <string>
#include "SDL.h"
#include "state.h"
#include "sprite.h"
#include "direction.h"

using namespace std;

class Agent : public Sprite {
    public:
        const int AGENT_W = 10;
        const int AGENT_H = 22;

        Agent(SDL_Renderer* renderer, GameState* state, SDL_Point pos);
        virtual ~Agent();

        void setPosition(SDL_Point pos);
        SDL_Point getPosition();

        virtual void update();

        void move(Direction dir);

        void render(SDL_Rect* rect);

    protected:
        SDL_Point pos;

        GameState* state;
};

struct PathNode {
    Direction dir;
    SDL_Point dest;
    unsigned short int g = 0xff;
    unsigned short int h = 0xff;
};

class PathNodeCompare {
    private:
        bool reverse;
    public:
        PathNodeCompare(const bool& reverse=false);
        bool operator() (const PathNode& lnode, const PathNode& rnode) const;
};

class PathfindingAgent : public Agent {
    public:
        PathfindingAgent(SDL_Renderer* renderer, GameState* state, SDL_Point position);
        virtual ~PathfindingAgent();

        void setDestination(SDL_Point dest);

        void update();

    protected:
        void searchPath();

    private:
        SDL_Point dest;

        list<PathNode> path;
        priority_queue<PathNode,vector<PathNode>,PathNodeCompare> queue;
};

#endif	/* _HEXNUL_AGENT_H_ */
