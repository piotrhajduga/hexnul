#ifndef	_HEXNUL_UTIL_H_
#define	_HEXNUL_UTIL_H_

#include <iostream>
#include <string>
#include <array>
#include "SDL.h"
#include "SDL_image.h"

#include "constants.h"

typedef enum {
    DEBUG, INFO, WARN, ERROR
} LogLevel;

typedef std::array<SDL_Point, 6> NeighborArray;

class Utils {
    private:
        static const LogLevel level = LOGGING_LEVEL;

    public:
        static void log(LogLevel ilevel, std::string file, int line, std::string message);

        static SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer);
        static NeighborArray getNeighbors(SDL_Point coord);
};

#define LOG(level, message) Utils::log(level, __FILE__, __LINE__, message)

#endif
