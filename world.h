#ifndef _HEXNUL_GAME_WORLD_H_
#define _HEXNUL_GAME_WORLD_H_

#include "SDL.h"
#include "SDL_image.h"

#include "state.h"

class GameWorld {
    public:
        GameWorld(SDL_Renderer *renderer, GameState *state);
        ~GameWorld();

        void draw();

        SDL_Point coordsForXY(SDL_Point point);

        void drawHex(SDL_Point coord);
        void fillHex(SDL_Point coord);

        void setHover(SDL_Point coord);
    private:
        GameState* state;

        const int HEX_H = 36;
        const int HEX_W = 48;
        const int GRID_ROW_H = HEX_H*3/4;
        const int GRID_ROW_TOP_H = HEX_H/4;

        SDL_Point* hoverCoord = NULL;

        SDL_Renderer* renderer;
        SDL_Texture* greenTile;
        SDL_Texture* redTile;
        SDL_Texture* blueTile;
        SDL_Surface* loadingSurface;

        SDL_Texture* loadTexture(const char *file);
};

#endif //_HEXNUL_GAME_WORLD_H_
