#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"

using namespace std;

void Utils::log(LogLevel ilevel, string file, int line, string message) {
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

SDL_Texture* Utils::loadTexture(string file, SDL_Renderer* renderer) {
    SDL_Texture* tx = NULL;
    LOG(INFO, string("Load surface from image: ")+file);
    SDL_Surface* loadingSurface = IMG_Load(file.c_str());
    if (loadingSurface == NULL) {
        LOG(ERROR, "Cannot load: "+file);
        return NULL;
    }
    SDL_SetSurfaceRLE(loadingSurface, 1);
    LOG(DEBUG, "Create texture from surface");
    tx = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    LOG(DEBUG, string("Free surface with image: ")+file);
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
