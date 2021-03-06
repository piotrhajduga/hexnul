#ifndef	_HEXNUL_MAPLOADER_H_
#define	_HEXNUL_MAPLOADER_H_

#include <string>

#include "worldstate.h"

using namespace std;

class MapLoader {
    public:
        MapLoader(WorldState* state, SDL_Renderer* renderer);
        ~MapLoader();

        void load(string mapFile, SDL_Point srcorigin, SDL_Point dstorigin, int radius);
    protected:
        SDL_Renderer* renderer;
        WorldState* state;
        string mapFile;
        SDL_Point origin;
        int radius;

        void setTileForPixel(SDL_Point coord, SDL_Color color);

    private:
        SDL_PixelFormat *format;
};

#endif //	_HEXNUL_MAPLOADER_H_
