#ifndef _HEXNUL_GAME_WORLD_H_
#define _HEXNUL_GAME_WORLD_H_

#include "SDL.h"
#include <set>

class GameWorld {
    public:
        GameWorld(SDL_Renderer *renderer);
        ~GameWorld();

        void draw();

        SDL_Point coordsForXY(SDL_Point point);
        void setActive(SDL_Point point);
        void setInactive(SDL_Point point);

        void drawHex(SDL_Point coord) {
            drawHex(coord.x, coord.y);
        }
        void drawHex(int col, int row);
    private:
        const int HEX_H = 36;
        const int HEX_W = 48;

        SDL_Renderer* renderer;

        struct compare {
            bool operator() (const SDL_Point& p1, const SDL_Point& p2) const {
                return p1.y<p2.y || p1.x<p2.x;
            }
        };

        std::set<SDL_Point, compare> hexs;
        std::set<SDL_Point, compare> activePoints;
};

#endif //_HEXNUL_GAME_WORLD_H_
