#ifndef	_HEXNUL_TILE_H_
#define	_HEXNUL_TILE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "constants.h"
#include "sprite.h"
#include "utils.h"
#include "tile.h"

using namespace std;

typedef enum {
    GRASS, WATER, DIRT, SAND
} TileType;

typedef struct {
    const char* textureFile;
    bool isContainer;
} TileData;

typedef unordered_map<TileType, TileData> TileTypeDataMap;

static TileTypeDataMap TILE_TYPE_DATA = {
    {GRASS, {TEXTURE_TILE_GRASS, true}},
    {WATER, {TEXTURE_TILE_WATER, false}},
    {DIRT, {TEXTURE_TILE_DIRT, true}},
    {SAND, {TEXTURE_TILE_SAND, false}},
};

class Tile : public Sprite {
    public:
        static Tile* getTile(TileType type, SDL_Renderer* renderer);

        Tile(TileType itype, SDL_Renderer* renderer);
        virtual ~Tile();

        TileType getType() { return type; }

        bool isContainer() { return _isContainer; }

    private:
        TileType type;
        bool _isContainer = false;
};

#endif	/* _HEXNUL_H_ */
