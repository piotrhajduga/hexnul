#include <string>

#include "sprite.h"
#include "utils.h"
#include "tile.h"

using namespace std;

SDL_Surface* Tile::tileMask = NULL;

SDL_Surface* Tile::getTileMask() {
    SDL_Surface* surf = NULL;
    if (tileMask == NULL) {
        LOG(DEBUG, string("Loading tileMask: ")+TILEMASK_TEXTURE_FILE);
        surf = IMG_Load(TILEMASK_TEXTURE_FILE.c_str());
        if (surf == NULL) {
            LOG(ERROR, string("Cannot load ")+TILEMASK_TEXTURE_FILE);
        }
        tileMask = SDL_ConvertSurface(surf, surf->format, 0);
        if (SDL_SetSurfaceBlendMode(tileMask, SDL_BLENDMODE_MOD)!=0) {
            LOG(ERROR, SDL_GetError());
        }
        SDL_FreeSurface(surf);
    }
    return tileMask;
}

SDL_Texture* Tile::getTexture(string textureFile, SDL_Renderer* renderer) {
    SDL_Surface* surf;
    SDL_Texture* tx = NULL;
    //SDL_Surface* _tileMask = Tile::getTileMask();

    LOG(DEBUG, string("Looking up texture: ")+textureFile);
    tx = Sprite::textureCache[textureFile];
    if (tx == NULL) {
        LOG(INFO, "Texture not loaded, loading...");
        surf = IMG_Load(textureFile.c_str());
        if (surf == NULL) {
            LOG(ERROR, "Cannot load "+textureFile);
            return NULL;
        }
        //if (SDL_BlitScaled(surf, NULL, _tileMask, NULL)!=0) {
            //LOG(ERROR, SDL_GetError());
        //}

        tx = SDL_CreateTextureFromSurface(renderer, surf);
        if (tx == NULL) {
            LOG(ERROR, SDL_GetError());
            return NULL;
        }
        Sprite::textureCache[textureFile] = tx;
        //SDL_FreeSurface(_tileMask);
        SDL_FreeSurface(surf);

    }
    return tx;
}

Tile::Tile(TileType itype, SDL_Renderer* renderer, string textureFile, bool isContainer)
    : Sprite(renderer, getTexture(textureFile, renderer)) {
    type = itype;
    _isContainer = isContainer;
}

Tile::~Tile() {}
