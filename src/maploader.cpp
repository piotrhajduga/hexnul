#include <map>
#include <string>
#include "stdio.h"

#include "utils.h"
#include "state.h"
#include "tile.h"
#include "maploader.h"

using namespace std;

MapLoader::MapLoader(GameState* istate, string imapFile, SDL_Point iorigin, int iradius) {
    state = istate;
    mapFile = imapFile;
    origin = iorigin;
    radius = iradius;

    load();
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
    LOG(INFO, string("Load surface from image: ")+mapFile);
    SDL_Surface* img = IMG_Load(mapFile.c_str());
    if (img == NULL) {
        LOG(ERROR, "Cannot load: "+mapFile);
        return;
    }

    format = img->format;

    SDL_LockSurface(img);

    SDL_Color color;
    for (int x=origin.x-radius;x<origin.x+radius;x++) {
        for (int y=origin.y-radius;y<origin.y+radius;y++) {
            color = format->palette->colors[((Uint32*) img->pixels)[y*img->h+x]];
            setTileForPixel({x+radius,y+radius}, color);
        }
    }

    SDL_UnlockSurface(img);

    LOG(DEBUG, string("Free surface with image: ")+mapFile);
    SDL_FreeSurface(img);
}

void MapLoader::setTileForPixel(SDL_Point coord, SDL_Color color) {
    if (LOGGING_LEVEL == DEBUG) {
        string log = string("setTileForPixel");
        log += " {"+to_string(coord.x)+","+to_string(coord.y)+"}";
        LOG(DEBUG, log);
        printf("%x%x%x%x\n", color.r, color.g, color.b, color.a);
    }
    //map<Uint32, TileType> pixel2TileType = {
        //{},
    //};
}
