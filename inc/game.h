#ifndef	_HEXNUL_H_
#define	_HEXNUL_H_

#include "SDL.h"

#include "state.h"
#include "world.h"
#include "tile.h"
#include "things.h"

#define COLORS 12

class Game {
    public:
        Game();

        int OnExecute();

        bool OnInit();

        void OnEvent(SDL_Event* event);

        void OnLoop();

        void OnRender();

        void OnCleanup();

        void OnClick(SDL_MouseButtonEvent* event);

        void OnMouseMove(SDL_MouseMotionEvent* event);
    private:
        const int FPS = 30;
        bool running;
        unsigned int ticks = 0;

        SDL_Window* display;
        SDL_Renderer* renderer;
        GameState state;
        GameWorld* world;

        TileFactory* tileFactory;
        ThingFactory* thingFactory;

        void drawHexs(int cols, int rows);
        void drawHex(int col, int row);
        void drawHex(SDL_Point offset);

        Road* createRoad(NeighborArray neighbors);
        void updateRoad(Road* road, NeighborArray neighbors);
        void updateNeighbors(NeighborArray neighbors, Thing* thing);
};

#endif	/* _HEXNUL_H_ */
