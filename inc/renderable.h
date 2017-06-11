#ifndef	_HEXNUL_RENDERABLE_H_
#define	_HEXNUL_RENDERABLE_H_

#include <iostream>
#include "SDL.h"
#include "utils.h"

class Renderable {
    protected:
        SDL_Renderer* renderer;

    public:
        Renderable(SDL_Renderer* iRenderer) {
            renderer = iRenderer;
        }
        virtual ~Renderable() {};

        virtual void render(SDL_Rect* rect) {
            LOG(WARN, "rendering base class");
        };
};

#endif	/* _HEXNUL_H_ */
