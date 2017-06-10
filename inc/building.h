#ifndef	_HEXNUL_BUILDING_H_
#define	_HEXNUL_BUILDING_H_

#include <string>
#include <list>
#include "SDL.h"
#include "utils.h"
#include "sprite.h"
#include "thing.h"

using namespace std;

static string BUILDING_TEXTURE_FILE = "assets/tiles/building.png";

class BuildingSegment : public Sprite, public Thing  {
    public:
        static const int BUILDING_SIZE = 15;

        BuildingSegment(SDL_Renderer* renderer);

        ThingType getType() const { return BUILDING; };

        void render(SDL_Rect* rect);
};

class Building : public std::list<Thing*>, public Thing {
    public:
        Building(SDL_Renderer* renderer);

        virtual ThingType getType() const { return STACK; };

        void grow();

        void shrink();

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_BUILDING_H_
