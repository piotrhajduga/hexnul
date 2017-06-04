#ifndef	_HEXNUL_TILE_FACTORY_H_
#define	_HEXNUL_TILE_FACTORY_H_

#include <string>
#include <unordered_map>
#include "tile.h"
#include "utils.h"

using namespace std;

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
            {GRASS, {"green.png", false}},
            {WATER, {"water.png", false}},
            {DIRT, {"dirt.png", true}},
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

#endif	/* _HEXNUL_TILE_FACTORY_H_ */
