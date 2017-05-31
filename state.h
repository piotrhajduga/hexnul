#ifndef	_HEXNUL_GAME_STATE_H_
#define	_HEXNUL_GAME_STATE_H_

#include "SDL.h"
#include <set>
#include <map>

#include "thing.h"

class GameState {
    public:
        struct comparePoints {
            bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
                return (p1.y<p2.y) || (p1.y==p2.y && p1.x<p2.x);
            }
        };

        GameState();
        ~GameState();

        typedef std::set<SDL_Point, GameState::comparePoints> PointSet;
        typedef std::map<SDL_Point, Thing*, comparePoints> ThingSet;

        void toggleGround(SDL_Point point);
        bool isGround(SDL_Point point);
        int countNeighbourGround(SDL_Point coord);

        PointSet getHexs();

        void putThing(SDL_Point coord, Thing* thing);
        void clearThing(SDL_Point coord);
        Thing* getThing(SDL_Point coord);
    private:
        //hexs is like an active region that user might act on
        PointSet hexs = {
                        {4,2},{5,2},
                  {3,3},{4,3},{5,3},{6,3},
                  {3,4},{4,4},{5,4},{6,4},{7,4},{8,4},
            {2,5},{3,5},{4,5},{5,5},{6,5},{7,5},{8,5},
            {2,6},{3,6},{4,6},{5,6},{6,6},{7,6},
            {2,7},{3,7},{4,7},{5,7},{6,7},
                        {4,8},{5,8},
        };

        PointSet ground;
        ThingSet things;
};

#endif	/* _HEXNUL_GAME_STATE_H_ */
