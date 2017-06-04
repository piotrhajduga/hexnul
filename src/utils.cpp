#include <iostream>

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
