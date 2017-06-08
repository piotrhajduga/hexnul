#ifndef _HEXNUL_GAME_WORLD_H_
#define _HEXNUL_GAME_WORLD_H_

#include <unordered_map>
#include <array>
#include "SDL.h"
#include "SDL_image.h"

#include "state.h"

#define WIN_W 1024
#define WIN_H 768
#define BOARD_OFFSET_X 0
#define BOARD_OFFSET_Y 0

class GameWorld {
    public:
        GameWorld(SDL_Renderer *renderer, GameState *state);
        ~GameWorld();

        SDL_Point coordsForXY(SDL_Point point);

        void initHexs(SDL_Point origin, int size);
        PointSet getHexs();

        void draw();

        void setHover(SDL_Point coord);

    protected:
        void drawHex(SDL_Point coord);
        void drawThings(SDL_Point coord, SDL_Rect* destRect);

    private:
        GameState* state;

        const char* HOVER_TEXTURE_FILE = "assets/ui/hover.png";

        int HEX_H = WIN_H/11;
        int HEX_W = WIN_W/11;
        int GRID_ROW_H = HEX_H*3/4;
        int GRID_ROW_TOP_H = HEX_H/4;

        //hexs is like an active region that user might act on
        PointSet hexs;

        SDL_Point offset;
        SDL_Point* hoverCoord = NULL;

        SDL_Renderer* renderer;
        Sprite* hover;

        std::unordered_map<TileType, SDL_Color> tileBorderColors = {
            {GRASS, {0x09, 0xb2, 0x1f, 255}},
            {WATER, {0x09, 0x12, 0xcf, 255}},
            {DIRT, {0xa9, 0x52, 0x1f, 255}},
            {SAND, {0xe9, 0xd2, 0x1f, 255}},
        };

        void drawHexOutline(SDL_Point coord);
};

#endif //_HEXNUL_GAME_WORLD_H_
