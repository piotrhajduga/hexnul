#ifndef	_HEXNUL_GAME_STATE_H_
#define	_HEXNUL_GAME_STATE_H_

#include "SDL.h"
#include <set>
#include <map>
#include <list>

#include "thing.h"

class GameState {
    public:
        static const int MAX_THING_STACK = 4;

        struct comparePoints {
            bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
                return (p1.y<p2.y) || (p1.y==p2.y && p1.x<p2.x);
            }
        };

        GameState();
        ~GameState();

        typedef std::set<SDL_Point, comparePoints> PointSet;
        typedef std::list<Thing*> ThingStack;
        typedef std::map<SDL_Point, ThingStack, comparePoints> ThingMap;

        void toggleGround(SDL_Point point);
        bool isGround(SDL_Point point);

        bool canPutThing(SDL_Point coord);
        int countThings(SDL_Point coord);
        void putThing(SDL_Point coord, Thing* thing);
        void clearThing(SDL_Point coord);
        Thing* getThing(SDL_Point coord);
        ThingStack getThings(SDL_Point coord);
    private:

        PointSet ground;
        ThingMap things;
};

#endif	/* _HEXNUL_GAME_STATE_H_ */
