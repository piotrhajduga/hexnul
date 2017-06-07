#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"

void Utils::log(LogLevel ilevel, std::string message) {
    if (ilevel >= level) {
        switch (ilevel) {
        case DEBUG:
            std::cout<<"D"; break;
        case INFO:
            std::cout<<"I"; break;
        case WARN:
            std::cout<<"W"; break;
        case ERROR:
            std::cout<<"E"; break;
        }
        std::cout<<" | "<<message<<std::endl;
    }
}

void Utils::log(LogLevel ilevel, std::string message, std::string file, int line) {
    if (ilevel >= level) {
        switch (ilevel) {
        case DEBUG:
            std::cout<<"D"; break;
        case INFO:
            std::cout<<"I"; break;
        case WARN:
            std::cout<<"W"; break;
        case ERROR:
            std::cout<<"E"; break;
        }
        std::cout<<" | "<<file<<":"<<line<<" | "<<message<<std::endl;
    }
}

SDL_Texture* Utils::loadTexture(const char *file, SDL_Renderer* renderer) {
    SDL_Surface* loadingSurface = IMG_Load(file);
    if (loadingSurface == NULL) {
        std::cout<<"Cannot load "<<file<<std::endl;
        return NULL;
    }
    SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    return tx;
}

NeighborArray Utils::getNeighbors(SDL_Point coord) {
    int row = coord.y, col=coord.x;
    return {
        col-1+(row%2), row-1,
        col+(row%2), row-1,
        col+1, row,
        col+(row%2), row+1,
        col-1+(row%2), row+1,
        col-1, row,
    };
}
