#include <unordered_map>
#include <string>

#include "SDL.h"

#include "utils.h"
#include "sprite.h"

using namespace std;

unordered_map<string, SDL_Texture*> Sprite::textureCache;

SDL_Texture* Sprite::getTexture() {
    return texture;
}

SDL_Texture* Sprite::getTexture(string textureFile, SDL_Renderer* renderer) {
    try {
        LOG(DEBUG, "Looking up texture");
        texture = Sprite::textureCache[textureFile];
        if (texture == NULL) {
            LOG(INFO, "Texture not loaded, loading...");
            texture = Utils::loadTexture(textureFile.c_str(), renderer);
        }
    } catch (const out_of_range& oor) {
        LOG(INFO, "Texture not loaded, loading...");
        texture = Utils::loadTexture(textureFile.c_str(), renderer);
    }
    LOG(DEBUG, string("Saving in texture cache: ")+textureFile);
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
    LOG(DEBUG, "Sprite::Sprite from existing texture");
    texture = iTexture;
    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
};

Sprite::Sprite(SDL_Renderer* renderer, string textureFile)
    : Renderable(renderer) {
    LOG(DEBUG, string("Sprite::Sprite ")+textureFile);
    texture = getTexture(textureFile, renderer);
    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
}

Sprite::Sprite(SDL_Renderer* renderer, string textureFile, SDL_BlendMode blend)
    : Renderable(renderer) {
    texture = getTexture(textureFile, renderer);
    SDL_SetTextureBlendMode(texture, blend);
    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
}

Sprite::~Sprite() {}

void Sprite::render(SDL_Rect* rect) {
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

SDL_Rect Sprite::getTextureRect() {
    return textureRect;
}
