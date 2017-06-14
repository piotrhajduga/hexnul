#ifndef _HEXNUL_GAME_WORLD_H_
#define _HEXNUL_GAME_WORLD_H_

#include <unordered_map>
#include <array>
#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"
#include "renderable.h"
#include "sprite.h"
#include "thing.h"
#include "tile.h"
#include "building.h"
#include "road.h"
#include "direction.h"
#include "toolbar.h"
#include "agent.h"
#include "state.h"

#define WIN_W 1024
#define WIN_H 768
#define BOARD_OFFSET_X 0
#define BOARD_OFFSET_Y 0

class GameWorld : public Renderable {
    public:
        GameWorld(SDL_Renderer *renderer, GameState *state, Toolbar* toolbar);
        virtual ~GameWorld();

        SDL_Point coordsForXY(SDL_Point point);

        void render(SDL_Rect* rect);

        void setHover(SDL_Point coord);

        void OnLoop();
        void OnClick(SDL_MouseButtonEvent* event);
        void OnMouseMove(SDL_MouseMotionEvent* event);
    protected:
        void initHexs(SDL_Point origin, int size);
        void insertHex(SDL_Point coord);
        void drawHex(SDL_Point coord);
        void drawHover(SDL_Point coord, SDL_Rect* rect);
        void drawThings(SDL_Point coord, SDL_Rect* destRect);

    private:
        GameState* state;
        Toolbar* toolbar;

        int VIEW_RADIUS = 10;
        int HEX_H = WIN_H/(VIEW_RADIUS*2-1);
        int HEX_W = WIN_W/(VIEW_RADIUS*2-1);
        int GRID_ROW_H = HEX_H*3/4;
        int GRID_ROW_TOP_H = HEX_H/4;

        //hexs is like an active region that user might act on
        PointSet hexs;

        PathfindingAgent* agent = NULL;

        SDL_Point offset;
        SDL_Point* hoverCoord = NULL;

        Sprite* empty;
        Sprite* hover;

        std::unordered_map<TileType, SDL_Color> tileBorderColors = {
            {GRASS, {0x09, 0xb2, 0x1f, 255}},
            {WATER, {0x09, 0x12, 0xcf, 255}},
            {DIRT, {0xa9, 0x52, 0x1f, 255}},
            {SAND, {0xe9, 0xd2, 0x1f, 255}},
        };

        Tile* generateRandomTile();

        void drawHexOutline(SDL_Point coord);
        SDL_Rect getHexRectForCoord(SDL_Point coord);

        void drawAgents();

        void updateRoadNode(RoadNode* road, NeighborArray neighbors);
        void updateNeighbors(NeighborArray neighbors, RoadNode* thing);
};

#endif //_HEXNUL_GAME_WORLD_H_
