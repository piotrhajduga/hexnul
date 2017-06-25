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
#include "gamestate.h"


class GameWorld : public Renderable {
    public:
        GameWorld(SDL_Renderer *renderer, GameState *state, Toolbar* toolbar);
        virtual ~GameWorld();

        SDL_Point coordsForXY(SDL_Point point);
        SDL_Rect getHexRectForCoord(SDL_Point coord);

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

        void updateDimensions(SDL_Rect* rect);

    private:
        GameState* state;
        Toolbar* toolbar;

        int viewRadius = 10;

        SDL_Rect winRect;

        int dim_mul = 2;
        int dim();
        SDL_Point centeringOffset = {0,0};
        SDL_Point hexDims;
        void updateHexDims();

        //hexs is like an active region that user might act on
        PointSet hexs;

        GoalOrientedAgent* agent = NULL;
        GoalQueue goals;

        //SDL_Point offset;
        SDL_Point* hoverCoord = NULL;

        Sprite* empty;
        Sprite* hover;
        Sprite* goalSprite;
        Sprite* goalSpriteActive;
        Sprite* goalSpriteRoad;
        Sprite* goalSpriteBuilding;

        Tile* generateRandomTile();

        void drawGoal(Goal goal, Sprite* sprite=NULL);
        void drawGoals();
        void drawAgents();

        void updateRoadNode(RoadNode* road, NeighborArray neighbors);
        void updateNeighbors(NeighborArray neighbors, RoadNode* thing);
};

#endif //_HEXNUL_GAME_WORLD_H_
