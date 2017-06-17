#ifndef	_HEXNUL_MAPLOADER_H_
#define	_HEXNUL_MAPLOADER_H_

#include <string>

#include "state.h"

using namespace std;

class MapLoader {
    public:
        MapLoader(GameState* state, string mapFile, SDL_Point origin, int radius);
        ~MapLoader();

        void load();
    protected:
        GameState* state;
        string mapFile;
        SDL_Point origin;
        int radius;

        void setTileForPixel(SDL_Point coord, SDL_Color color);

    private:
        SDL_PixelFormat *format;
};

#endif //	_HEXNUL_MAPLOADER_H_
