#ifndef	_HEXNUL_SPRITE_H_
#define	_HEXNUL_SPRITE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"
#include "renderable.h"

using namespace std;

class Sprite : public Renderable {
    protected:
        static unordered_map<string, SDL_Texture*> textureCache;

    public:
        static void clearTextureCache();

        Sprite(SDL_Renderer* renderer, SDL_Texture* iTexture);
        Sprite(SDL_Renderer* renderer, string textureFile);
        Sprite(SDL_Renderer* renderer, string textureFile, SDL_BlendMode blend);
        virtual ~Sprite();

        void render(SDL_Rect* rect);

        SDL_Texture* getTexture();
        SDL_Texture* getTexture(string textureFile, SDL_Renderer* renderer);

        SDL_Rect getTextureRect();
    private:
        SDL_Texture* texture;
        SDL_Rect textureRect = {0,0,0,0};
};

#endif	/* _HEXNUL_H_ */
