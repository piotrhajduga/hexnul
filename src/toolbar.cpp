#include <string>
#include "utils.h"
#include "tile.h"
#include "building.h"
#include "road.h"
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

    hover = new Sprite(renderer, TEXTURE_TOOL_HOVER, SDL_BLENDMODE_BLEND);
    active = new Sprite(renderer, TEXTURE_TOOL_ACTIVE, SDL_BLENDMODE_BLEND);

    initTools();
}

Toolbar::~Toolbar() {
    for (auto pair : toolSprites) {
        delete pair.second;
    }
    delete hover;
    delete active;
    if (agent != NULL) {
        delete agent;
    }
}

ToolType Toolbar::toolTypeForXY(SDL_Point point) {
    try {
        return intToToolType.at(point.x/ACTIVE_W);
    } catch (const out_of_range& oor) {
        return ToolType::NONE;
    }
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
    int i = 0;
    for (auto it : toolSprites) {
        intToToolType[i] = it.first;
        if (it.first != ToolType::NONE) {
            if (activeTool == it.first) {
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
            it.second->render(&rect);
            if (hoverTool == it.first) {
                hover->render(&rect);
            }
        }
        i++;
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

Sprite* Toolbar::getActiveToolSprite() {
    try {
        return toolSprites.at(activeTool);
    } catch (const out_of_range& oor) {
        return NULL;
    }
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

void Toolbar::useActiveTool(SDL_Point coord) {
    Tile* ground = state->getGround(coord);
    Thing* thing = state->getThing(coord);

    switch (getActive()) {
    case ToolType::GRASS:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set GRASS");
            state->setGround(coord, new Tile(GRASS, renderer));
        }
        break;
    case ToolType::WATER:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set WATER");
            state->setGround(coord, new Tile(WATER, renderer));
        }
        break;
    case ToolType::DIRT:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set DIRT");
            state->setGround(coord, new Tile(DIRT, renderer));
        }
        break;
    case ToolType::SAND:
        if (thing == NULL && ground == NULL) {
            LOG(DEBUG, "Set SAND");
            state->setGround(coord, new Tile(SAND, renderer));
        }
        break;
    case ToolType::ROAD:
        if (ground!=NULL && ground->isContainer() && thing==NULL) {
            LOG(DEBUG, "Put ROAD");
            state->addGoal({Goal::BUILD, 5, coord, BuildType::ROAD});
        }
        break;
    case ToolType::BUILDING:
        if (ground!=NULL && ground->isContainer()) {
            LOG(DEBUG, "Create goal: Building");
            state->addGoal({Goal::BUILD, 3, coord, BuildType::HOUSE});
        }
        break;
    case ToolType::AGENT:
        if (ground != NULL) {
            LOG(DEBUG, "Create new GOAgent");
            state->addAgent(new GOAgent(renderer, state, coord));
        }
        break;
    case ToolType::DESTROY:
        LOG(DEBUG, "Destroy!");
        if (state->countThings(coord) > 0) {
            LOG(DEBUG, "Oh, there's a thing! Destroy!");
            state->clearThing(coord);
        //} else if (ground != NULL) {
            //LOG(DEBUG, "Oh, there's ground! Destroy!");
            //state->removeGround(coord);
        }
        break;
    default:
        //idle
        break;
    }
}

Agent* Toolbar::getAgent() {
    return agent;
}
