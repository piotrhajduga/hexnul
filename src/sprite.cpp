#include <string>
#include "utils.h"
#include "sprite.h"

using namespace std;

map<string, SDL_Texture*> Sprite::textureCache;

SDL_Texture* Sprite::getTexture(string textureFile, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    try {
        LOG(DEBUG, "Looking up texture");
        texture = Sprite::textureCache[textureFile];
        if (texture == NULL) {
            texture = Utils::loadTexture(textureFile.c_str(), renderer);
        }
    } catch (const out_of_range& oor) {
        LOG(INFO, "Texture not loaded, loading...");
        texture = Utils::loadTexture(textureFile.c_str(), renderer);
    }
    Sprite::textureCache[textureFile] = texture;
    return texture;
}

void Sprite::clearTextureCache() {
    LOG(DEBUG, "Cleaning Sprite textures");
    for (auto it : textureCache) {
        SDL_DestroyTexture(it.second);
    }
}

Sprite::Sprite(SDL_Renderer* renderer, SDL_Texture* iTexture)
    : Renderable(renderer) {
    texture = iTexture;
};

Sprite::Sprite(SDL_Renderer* renderer, string textureFile)
    : Renderable(renderer) {
    texture = getTexture(textureFile, renderer);
}

Sprite::Sprite(SDL_Renderer* renderer, string textureFile, SDL_BlendMode blend)
    : Renderable(renderer) {
    texture = getTexture(textureFile, renderer);
    SDL_SetTextureBlendMode(texture, blend);
}

Sprite::~Sprite() {
}

void Sprite::render(SDL_Rect* rect) {
    SDL_RenderCopy(renderer, texture, NULL, rect);
}
