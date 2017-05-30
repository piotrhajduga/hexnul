#ifndef	_HEXNUL_GAME_STATE_H_
#define	_HEXNUL_GAME_STATE_H_

#include "SDL.h"
#include <set>

class GameState {
    private:
        struct compare {
            bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
                return (p1.y<p2.y) || (p1.y==p2.y && p1.x<p2.x);
            }
        };
    public:
        GameState();
        ~GameState();

        typedef std::set<SDL_Point, GameState::compare> PointSet;

        void toggleActive(SDL_Point point);
        bool isActive(SDL_Point point);
        PointSet getHexs();
    private:
        PointSet hexs = {
            {0, 0},{0, 1},{0, 2},{0, 6},{0, 8},
            {1, 0},{1, 1},{1, 4},{1, 6},{1, 7},{1, 8},
            {2, 2},{2, 3},{2, 4},{2, 8},{2, 9},
            {3, 2},{3, 3},{3, 4},{3, 7},{3, 8},
            {7, 0},{7, 3},{7, 5},{7, 6},{7, 7},
            {8, 3},{8, 4},{8, 6},
            {9, 2},{9, 3},{9, 4},{9, 6}
        };
        PointSet activePoints;
};

#endif	/* _HEXNUL_GAME_STATE_H_ */
