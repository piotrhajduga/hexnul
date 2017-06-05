#ifndef	_HEXNUL_SPRITE_H_
#define	_HEXNUL_SPRITE_H_

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"
#include "renderable.h"

class Sprite : public Renderable {
    public:
        Sprite(SDL_Renderer* renderer, SDL_Texture* iTexture)
            : Renderable(renderer) {
            texture = iTexture;
        };
        Sprite(SDL_Renderer* renderer, const char* textureFile)
            : Renderable(renderer) {
            texture = Utils::loadTexture(textureFile, renderer);
        }
        virtual ~Sprite() {
            SDL_DestroyTexture(texture);
        }

        void render(SDL_Rect* rect) {
            SDL_RenderCopy(renderer, texture, NULL, rect);
        }
    private:
        SDL_Texture* texture;
};

#endif	/* _HEXNUL_H_ */
