#ifndef	_HEXNUL_GAME_THING_H_
#define	_HEXNUL_GAME_THING_H_

#include "SDL.h"

class Thing {
    public:
        Thing(SDL_Renderer* renderer);
        ~Thing();

        void render(SDL_Rect* rect);
    private:
        SDL_Renderer* renderer;
        SDL_Texture* tx;

        SDL_Texture* loadTexture(const char *file);
};

#endif	/* _HEXNUL_GAME_THING_H_ */
