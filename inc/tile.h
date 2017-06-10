#ifndef	_HEXNUL_TILE_H_
#define	_HEXNUL_TILE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

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

const string TILEMASK_TEXTURE_FILE = "assets/tiles/tile_mask.png";

static TileTypeDataMap TILE_TYPE_DATA = {
    {GRASS, {"assets/tiles/grass.png", true}},
    {WATER, {"assets/tiles/water.png", false}},
    {DIRT, {"assets/tiles/dirt.png", true}},
    {SAND, {"assets/tiles/sand.png", false}},
};

class Tile : public Sprite {
    public:
        typedef unordered_map<TileType, Tile*> TileTypeMap;

    private:
        static SDL_Surface* tileMask;
        static SDL_Surface* getTileMask();

        TileType type;
        bool _isContainer = false;

        static TileTypeMap typeobjs;

    public:
        static Tile* getTile(TileType type, SDL_Renderer* renderer);

        Tile(TileType itype, SDL_Renderer* renderer);
        virtual ~Tile();

        virtual SDL_Texture* getTexture(string textureFile, SDL_Renderer* renderer);

        TileType getType() { return type; }

        bool isContainer() { return _isContainer; }
};
#endif	/* _HEXNUL_H_ */
