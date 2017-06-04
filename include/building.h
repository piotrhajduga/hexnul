#ifndef	_HEXNUL_BUILDING_SEGMENT_H_
#define	_HEXNUL_BUILDING_SEGMENT_H_

#include "SDL.h"
#include "sprite.h"
#include "thing.h"

class BuildingSegment : public Thing, public Sprite {
    public:
        BuildingSegment(SDL_Renderer* renderer, const char *textureFile)
            : Thing(renderer), Sprite (renderer, textureFile) {}

        BuildingSegment(SDL_Renderer* renderer, const char *textureFile, int iheight)
            : Thing(renderer, iheight), Sprite (renderer, textureFile) {}

        ThingType getType() { return BUILDING; };

        void render(SDL_Rect* rect) {
            Sprite::render(rect);
        }
};

#endif	/* _HEXNUL_BASE_THING_H_ */
