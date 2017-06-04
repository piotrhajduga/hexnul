#ifndef	_HEXNUL_RENDERABLE_H_
#define	_HEXNUL_RENDERABLE_H_

#include "SDL.h"

class Renderable {
    protected:
        SDL_Renderer* renderer;

    public:
        Renderable(SDL_Renderer* iRenderer) {
            renderer = iRenderer;
        }
        ~Renderable() {};

        virtual void render(SDL_Rect* rect) {};
};

#endif	/* _HEXNUL_H_ */
