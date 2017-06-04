#ifndef	_HEXNUL_TILE_H_
#define	_HEXNUL_TILE_H_

#include "SDL.h"
#include "SDL_image.h"

#include "sprite.h"

typedef enum {
    GRASS, WATER, DIRT, SAND
} TileType;

class Tile : public Sprite {
    private:
        TileType type;
        bool _isContainer = false;

    public:
        Tile(TileType itype, SDL_Renderer* renderer, const char *textureFile, bool isContainer)
            : Sprite(renderer, textureFile) {
            type = itype;
            _isContainer = isContainer;
        }
        virtual ~Tile() {};

        TileType getType() { return type; }

        bool canPutThing() { return _isContainer; }
};

#endif	/* _HEXNUL_H_ */
