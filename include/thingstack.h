#ifndef	_HEXNUL_THING_STACK_H_
#define	_HEXNUL_THING_STACk_H_
#include <list>
#include "SDL.h"
#include "base_thing.h"

class ThingStack : public std::list<Thing*>, public Thing {
    public:
        ThingStack(SDL_Renderer* renderer)
            : Thing(renderer, 0) {}

        void putThing(Thing* thing) {
            height += thing->height;
            push_front(thing);
        }

        Thing* takeThing() {
            Thing* thing = front();
            height -= thing->height;
            pop_front();
            return thing;
        }

        void render(SDL_Rect* rect) {
            SDL_Rect DestR = *rect;
            for (ThingStack::reverse_iterator it=rbegin();
                    it!=rend();++it) {
                (*it)->render(&DestR);
                DestR.y-=(*it)->height;
            }
        }

        ThingType getType() { return STACK; };
};

#endif //_HEXNUL_THING_STACK_H_
