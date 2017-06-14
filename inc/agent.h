#ifndef	_HEXNUL_AGENT_H_
#define	_HEXNUL_AGENT_H_

#include <list>
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
        void move(SDL_Point coord);

        SDL_Point pos;

        GameState* state;
};

class PathfindingAgent : public Agent {
    public:
        PathfindingAgent(SDL_Renderer* renderer, GameState* state, SDL_Point position);
        virtual ~PathfindingAgent();

        void setDestination(SDL_Point dest);

        void update();

    protected:
        bool findPath();

    private:
        int lastMoveTicks = 0;

        SDL_Point dest;

        list<SDL_Point> path;

        bool isPassable(SDL_Point point);

        int gscore(SDL_Point point);

        int hscore(SDL_Point point);
};

#endif	/* _HEXNUL_AGENT_H_ */
