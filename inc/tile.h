#ifndef	_HEXNUL_TILE_H_
#define	_HEXNUL_TILE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "constants.h"
#include "pathnode.h"
#include "sprite.h"
#include "utils.h"
#include "tile.h"

using namespace std;

typedef enum {
    GRASS, WATER, DIRT, SAND, STONE
} TileType;

typedef struct {
    const char* textureFile;
    bool isContainer;
    bool isPassable;
    int moveCost;
} TileData;

typedef unordered_map<TileType, TileData> TileTypeDataMap;

static TileTypeDataMap TILE_TYPE_DATA = {
    {GRASS, {TEXTURE_TILE_GRASS, true, true, 10}},
    {WATER, {TEXTURE_TILE_WATER, false, true, 1000}},
    {DIRT, {TEXTURE_TILE_DIRT, true, true, 14}},
    {SAND, {TEXTURE_TILE_SAND, false, true, 30}},
    {STONE, {TEXTURE_TILE_STONE, false, true, 50}},
};

class Tile : public Sprite, public PathNode {
    public:
        static Tile* getTile(TileType type, SDL_Renderer* renderer);

        Tile(TileType itype, SDL_Renderer* renderer);
        virtual ~Tile();

        TileType getType() { return type; }

        bool isContainer() { return _isContainer; }

        int getMoveCost();
        bool isPassable();
    private:
        int moveCost = 0;
        int passable = true;
        TileType type;
        bool _isContainer = false;
};

#endif	/* _HEXNUL_H_ */
