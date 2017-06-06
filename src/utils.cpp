#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"

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

void Utils::log(LogLevel ilevel, std::string message) {
    if (ilevel >= level) {
        switch (ilevel) {
        case DEBUG:
            std::cout<<"D "; break;
        case INFO:
            std::cout<<"I "; break;
        case WARN:
            std::cout<<"W "; break;
        case ERROR:
            std::cout<<"E "; break;
        }
        std::cout<<message<<std::endl;
    }
}
