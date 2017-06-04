#ifndef	_HEXNUL_UTIL_H_
#define	_HEXNUL_UTIL_H_

#include "SDL.h"
#include "SDL_image.h"

class Utils {
    public:
        static SDL_Texture* loadTexture(const char *file, SDL_Renderer* renderer);
};

#endif
