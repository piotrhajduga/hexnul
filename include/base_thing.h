#ifndef	_HEXNUL_BASE_THING_H_
#define	_HEXNUL_BASE_THING_H_

#include "SDL.h"
#include "renderable.h"

typedef enum {
    THING, BUILDING, STACK
} ThingType;

class Thing : public Renderable {
    public:
        int height = 0;
        Thing(SDL_Renderer* renderer)
            : Renderable (renderer) {}
        Thing(SDL_Renderer* renderer, int iheight)
            : Renderable (renderer) {
                height = iheight;
            }
        virtual ~Thing() {};
        virtual void init() {};
        virtual ThingType getType() { return THING; };
};

#endif	/* _HEXNUL_BASE_THING_H_ */
