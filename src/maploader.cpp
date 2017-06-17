#include <map>
#include <string>
#include "stdio.h"

#include "utils.h"
#include "state.h"
#include "tile.h"
#include "maploader.h"

using namespace std;

MapLoader::MapLoader(GameState* istate, SDL_Renderer* irenderer) {
    state = istate;
    renderer = irenderer;
}

MapLoader::~MapLoader() {
}

void MapLoader::load(string mapFile, SDL_Point srcorigin, SDL_Point dstorigin, int radius) {
    LOG(INFO, string("Load surface from image: ")+mapFile);
    SDL_Surface* img = IMG_Load(mapFile.c_str());
    if (img == NULL) {
        LOG(ERROR, "Cannot load: "+mapFile);
        return;
    }

    format = img->format;

    SDL_LockSurface(img);

    Uint32 pixel;
    SDL_Color color;
    for (int x=-radius;x<radius;x++) {
        for (int y=-radius;y<radius;y++) {
            pixel = ((Uint32*) img->pixels)[((srcorigin.y+y)*img->h)+(srcorigin.x+x)];
            SDL_GetRGBA(pixel, format, &color.r, &color.g, &color.b, &color.a);
            setTileForPixel({x+dstorigin.x,y+dstorigin.y}, color);
        }
    }

    SDL_UnlockSurface(img);

    LOG(DEBUG, string("Free surface with image: ")+mapFile);
    SDL_FreeSurface(img);
}

void MapLoader::setTileForPixel(SDL_Point coord, SDL_Color color) {
    Uint32 pixel = (color.r<<24) | (color.g<<16) | (color.b<<8) | color.a;
    if (LOGGING_LEVEL == DEBUG) {
        printf("setTileForPixel {%i,%i} %02x%02x%02x%02x\n", coord.x, coord.y, color.r, color.g, color.b, color.a);
    }
    map<Uint32, TileType> pixel2TileType = {
        {0x0018ffff, WATER},
        {0xa0a0a0ff, STONE},
        {0x00b000ff, GRASS},
        {0xb09060ff, DIRT},
        {0xf0f060ff, SAND},
    };

    try {
        TileType type = pixel2TileType.at(pixel);
        state->setGround(coord, new Tile(type, renderer));
    } catch (const out_of_range& oor) {
        LOG(WARN, string("TileType not found for pixel ")+to_string(pixel));
    }
}
