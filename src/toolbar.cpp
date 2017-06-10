#include <string>
#include "utils.h"
#include "toolbar.h"


const char* toString(ToolType type) {
    switch(type) {
    case ToolType::GRASS: return "ToolType::GRASS";
    case ToolType::WATER: return "ToolType::WATER";
    case ToolType::DIRT: return "ToolType::DIRT";
    case ToolType::SAND: return "ToolType::SAND";
    case ToolType::ROAD: return "ToolType::ROAD";
    case ToolType::BUILDING: return "ToolType::BUILDING";
    case ToolType::DESTROY: return "ToolType::DESTROY";
    default:
    case ToolType::NONE: return "ToolType::NONE";
    }
}

Toolbar::Toolbar(SDL_Renderer *renderer, GameState *istate)
    : Renderable(renderer) {
    state = istate;

    hover = new Sprite(renderer, HOVER_TEXTURE_FILE, SDL_BLENDMODE_ADD);
    active = new Sprite(renderer, ACTIVE_TEXTURE_FILE, SDL_BLENDMODE_BLEND);

    initTools();
}

Toolbar::~Toolbar() {
    for (auto pair : toolSprites) {
        delete pair.second;
    }
    delete hover;
    delete active;
}

ToolType Toolbar::toolTypeForXY(SDL_Point point) {
    int x = point.x/ACTIVE_W;
    return (x>int(ToolType::NONE))?ToolType::NONE:(ToolType)x;
}

void Toolbar::initTools() {
    for (auto pair : TOOL_TEXTURES) {
        LOG(DEBUG, string("Load tool sprite: ")+pair.second);
        toolSprites[pair.first] = new Sprite(renderer, pair.second);
    }
}

void Toolbar::render(SDL_Rect* irect) {
    SDL_SetRenderDrawColor(renderer, 0x57, 0x5f, 0x4f, 255);
    SDL_RenderFillRect(renderer, irect);

    SDL_Rect rect;

    for (int i=0;i<(int)toolSprites.size();++i) {
        if (i != int(ToolType::NONE)) {
            if (activeTool == ToolType(i)) {
                rect = {
                    irect->x+i*ACTIVE_W,
                    irect->y+((irect->h-ACTIVE_H)/2), // centering on Y
                    ACTIVE_W,
                    ACTIVE_H
                };
                active->render(&rect);
            }
            rect = {
                irect->x+i*ACTIVE_W+(ACTIVE_W-TOOL_W)/2, //centering in ACTIVE
                irect->y+((irect->h-ACTIVE_H)/2)+(ACTIVE_H-TOOL_H)/2, // centering in ACTIVE
                TOOL_W,
                TOOL_H
            };
            toolSprites[ToolType(i)]->render(&rect);
            if (hoverTool == ToolType(i)) {
                hover->render(&rect);
            }
        }
    }
}

void Toolbar::setHover(ToolType type) {
    hoverTool = type;
}

void Toolbar::setActive(ToolType toolType) {
    LOG(DEBUG, string("Setting active tool: ")+toString(toolType));
    activeTool = toolType;
}

ToolType Toolbar::getActive() {
    return activeTool;
}

void Toolbar::OnClick(SDL_MouseButtonEvent* event) {
    ToolType type = toolTypeForXY({event->x, event->y});
    if (type != ToolType::NONE) {
        activeTool = type;
    }
}

void Toolbar::OnMouseMove(SDL_MouseMotionEvent* event) {
    setHover(toolTypeForXY({event->x, event->y}));
}
