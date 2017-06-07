#ifndef	_HEXNUL_BASE_THING_H_
#define	_HEXNUL_BASE_THING_H_

#include <string>
#include <unordered_map>
#include "SDL.h"
#include "renderable.h"
#include "thingtype.h"

class Thing : public Renderable {
    public:
        int height = 0;

        Thing(SDL_Renderer* renderer);
        Thing(SDL_Renderer* renderer, int height);
        virtual ~Thing() {};

        virtual ThingType getType() const {
            return THING;
        };

        virtual void init() {};
};

#endif	/* _HEXNUL_BASE_THING_H_ */
