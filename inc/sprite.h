#ifndef	_HEXNUL_SPRITE_H_
#define	_HEXNUL_SPRITE_H_

#include <map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "utils.h"
#include "renderable.h"

using namespace std;

class Sprite : public Renderable {
    public:
        static map<string, SDL_Texture*> textureCache;
        static SDL_Texture* getTexture(string textureFile, SDL_Renderer* renderer);
        static void clearTextureCache();

        Sprite(SDL_Renderer* renderer, SDL_Texture* iTexture);
        Sprite(SDL_Renderer* renderer, string textureFile);
        virtual ~Sprite();

        void render(SDL_Rect* rect);
    private:
        SDL_Texture* texture;
};

#endif	/* _HEXNUL_H_ */
