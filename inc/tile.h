#ifndef	_HEXNUL_TILE_H_
#define	_HEXNUL_TILE_H_

#include <unordered_map>

#include "SDL.h"
#include "SDL_image.h"

#include "sprite.h"
#include "utils.h"

using namespace std;

typedef enum {
    GRASS, WATER, DIRT, SAND
} TileType;

const string TILEMASK_TEXTURE_FILE = "assets/tiles/tile_mask.png";

class Tile : public Sprite {
    private:
        static SDL_Surface* tileMask;
        static SDL_Surface* getTileMask();

        TileType type;
        bool _isContainer = false;

    public:
        Tile(TileType itype, SDL_Renderer* renderer, string textureFile, bool isContainer);
        virtual ~Tile();

        virtual SDL_Texture* getTexture(string textureFile, SDL_Renderer* renderer);

        TileType getType() { return type; }

        bool canPutThing() { return _isContainer; }
};

typedef struct {
    const char* textureFile;
    bool isContainer;
} TileData;

typedef unordered_map<TileType, TileData> TileTypeDataMap;
typedef unordered_map<TileType, Tile*> TileTypeMap;

class TileFactory {
    private:
        SDL_Renderer* renderer;

    protected:
        TileTypeDataMap types = {
            {GRASS, {"assets/tiles/green.png", false}},
            {WATER, {"assets/tiles/water.png", false}},
            {DIRT, {"assets/tiles/dirt.png", true}},
            {SAND, {"assets/tiles/sand.png", true}},
        };
        TileTypeMap tiles;

    public:
        TileFactory(SDL_Renderer* irenderer) {
            TileData data;
            renderer = irenderer;
            for (TileTypeDataMap::iterator it=types.begin();it!=types.end();++it) {
                data = it->second;
                tiles[it->first] = new Tile(it->first, renderer, data.textureFile, data.isContainer);
            }
        }

        ~TileFactory() {
            for (TileTypeMap::iterator it=tiles.begin();it!=tiles.end();++it) {
                delete it->second;
            }
        }

        Tile* create(TileType type) {
            TileTypeMap::iterator it = tiles.find(type);
            if (it==tiles.end()) {
                return NULL;
            } else {
                return it->second;
            }
        }
};

#endif	/* _HEXNUL_H_ */
