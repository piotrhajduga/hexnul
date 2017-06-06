#ifndef	_HEXNUL_UTIL_H_
#define	_HEXNUL_UTIL_H_

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

typedef enum {
    DEBUG, INFO, WARN, ERROR
} LogLevel;

class Utils {
    private:
        static const LogLevel level = WARN;

    public:
        static SDL_Texture* loadTexture(const char *file, SDL_Renderer* renderer);
        static void log(LogLevel level, std::string msg);
};

#endif
