#ifndef _HEXNUL_TOOLBAR_H_
#define _HEXNUL_TOOLBAR_H_

#include <map>
#include <functional>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "constants.h"
#include "utils.h"

#include "renderable.h"
#include "agent.h"
#include "sprite.h"
#include "gamestate.h"

enum class ToolType {
    AGENT,
    GRASS,
    WATER,
    DIRT,
    SAND,
    ROAD,
    BUILDING,
    DESTROY,
    NONE
};

using namespace std;

class Toolbar : public Renderable {
    public:
        static const int ACTIVE_W = 80;
        static const int ACTIVE_H = 60;
        static const int TOOL_W = 80;
        static const int TOOL_H = 60;
        
        Toolbar(SDL_Renderer *renderer, GameState *state);
        virtual ~Toolbar();

        ToolType toolTypeForXY(SDL_Point point);

        void initTools();

        void render(SDL_Rect* rect);

        void setHover(ToolType type);

        void setActive(ToolType toolType);
        ToolType getActive();

        Sprite* getActiveToolSprite();

        void OnClick(SDL_MouseButtonEvent* event);
        void OnMouseMove(SDL_MouseMotionEvent* event);

        void useActiveTool(SDL_Point coord);
        Agent* getAgent();

    private:
        GameState* state;

        const map<ToolType, string> TOOL_TEXTURES = {
            //{ToolType::GRASS, TEXTURE_TOOL_GRASS},
            //{ToolType::WATER, TEXTURE_TILE_WATER},
            //{ToolType::DIRT, TEXTURE_TOOL_DIRT},
            //{ToolType::SAND, TEXTURE_TOOL_SAND},
            {ToolType::ROAD, TEXTURE_TOOL_ROAD},
            {ToolType::BUILDING, TEXTURE_TOOL_BUILDING},
            {ToolType::AGENT, TEXTURE_TOOL_AGENT},
            {ToolType::DESTROY, TEXTURE_TOOL_DESTROY},
        };
        map<int, ToolType> intToToolType;
        map<ToolType, Sprite*> toolSprites;

        ToolType activeTool = ToolType::NONE;
        ToolType hoverTool = ToolType::NONE;

        Sprite* hover;
        Sprite* active;

        Agent* agent = NULL;
};

#endif //_HEXNUL_TOOLBAR_H_
