#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "constants.h"
#include "utils.h"
#include "sprite.h"
#include "tile.h"

using namespace std;

Tile::Tile(TileType itype, SDL_Renderer* renderer)
    : Sprite(renderer, TILE_TYPE_DATA.at(itype).textureFile) {
    LOG(DEBUG, "new Tile()");
    type = itype;
    _isContainer = TILE_TYPE_DATA.at(itype).isContainer;
    moveCost = TILE_TYPE_DATA.at(itype).moveCost;
    passable = TILE_TYPE_DATA.at(itype).isPassable;
}

Tile::~Tile() {}

bool Tile::isPassable() {
    return passable;
}

int Tile::getMoveCost() {
    return moveCost;
}
