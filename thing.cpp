#include "SDL.h"
#include "SDL_image.h"
#include "thing.h"
#include <iostream>

Thing::Thing(SDL_Renderer* irenderer){
    renderer = irenderer;
    tx = loadTexture("building.png");
}
Thing::~Thing() {}

void Thing::render(SDL_Rect* rect) {
    SDL_RenderCopy(renderer, tx, NULL, rect);
}

SDL_Texture* Thing::loadTexture(const char *file) {
    SDL_Surface* loadingSurface = IMG_Load(file);
    if (loadingSurface == NULL) {
        std::cout<<"Cannot load "<<file<<std::endl;
        return NULL;
    }
    SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    return tx;
}
