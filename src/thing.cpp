#include "thing.h"

Thing::Thing(SDL_Renderer* renderer) : Renderable (renderer) {}

Thing::Thing(SDL_Renderer* renderer, int iheight)
    : Renderable (renderer)
{
    height = iheight;
}
