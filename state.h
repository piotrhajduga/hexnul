#ifndef	_HEXNUL_GAME_STATE_H_
#define	_HEXNUL_GAME_STATE_H_

#include <set>
#include <unordered_map>
#include <list>

#include "SDL.h"

#include "thing.h"

struct hashCoord {
    int operator() (const SDL_Point& p1) const {
        return p1.x*4000 + p1.y;
    }
};

struct equalsCoords {
    bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
        return p1.x==p2.x && p1.y==p2.y;
    }
};

struct compareCoords {
    bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
        return (p1.y<p2.y) || (p1.y==p2.y && p1.x<p2.x);
    }
};

typedef std::unordered_map<SDL_Point, Tile*, hashCoord, equalsCoords> TileMap;

typedef std::set<SDL_Point, compareCoords> PointSet;

typedef std::list<Thing*> ThingStack;
typedef std::unordered_map<SDL_Point, ThingStack, hashCoord, equalsCoords> ThingMap;

class GameState {
    public:
        static const int MAX_THING_STACK = 4;

        GameState();
        ~GameState();

        Tile* getGround(SDL_Point coord);
        void setGround(SDL_Point point, Tile* tile);
        void removeGround(SDL_Point point);
        bool isGround(SDL_Point point);

        int countThings(SDL_Point coord);
        void putThing(SDL_Point coord, Thing* thing);
        void clearThing(SDL_Point coord);
        Thing* getThing(SDL_Point coord);
        ThingStack getThings(SDL_Point coord);
    private:
        TileMap ground;
        ThingMap things;
};

#endif	/* _HEXNUL_GAME_STATE_H_ */
