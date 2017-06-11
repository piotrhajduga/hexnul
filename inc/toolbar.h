#ifndef _HEXNUL_TOOLBAR_H_
#define _HEXNUL_TOOLBAR_H_

#include <unordered_map>
#include <functional>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"

#include "renderable.h"
#include "sprite.h"
#include "state.h"

enum class ToolType {
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
        static const int ACTIVE_W = 90;
        static const int ACTIVE_H = 90;
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

    private:
        GameState* state;

        const char* HOVER_TEXTURE_FILE = "assets/ui/hover.png";
        const char* ACTIVE_TEXTURE_FILE = "assets/ui/active.png";

        const unordered_map<ToolType, string> TOOL_TEXTURES = {
            {ToolType::GRASS, "assets/ui/grass.png"},
            {ToolType::WATER, "assets/ui/water.png"},
            {ToolType::DIRT, "assets/ui/dirt.png"},
            {ToolType::SAND, "assets/ui/sand.png"},
            {ToolType::ROAD, "assets/ui/road.png"},
            {ToolType::BUILDING, "assets/ui/home_0.png"},
            {ToolType::DESTROY, "assets/ui/destroy.png"},
        };
        unordered_map<ToolType, Sprite*> toolSprites;

        ToolType activeTool = ToolType::NONE;
        ToolType hoverTool = ToolType::NONE;

        Sprite* hover;
        Sprite* active;
};

#endif //_HEXNUL_TOOLBAR_H_
