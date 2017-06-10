#ifndef	_HEXNUL_BUILDING_H_
#define	_HEXNUL_BUILDING_H_

#include <array>
#include <string>
#include <list>
#include "SDL.h"
#include "utils.h"
#include "sprite.h"
#include "thing.h"

using namespace std;

static string BUILDINGSEGMENT_TEXTURE_FILE = "assets/tiles/building.png";

class BuildingSegment : public Sprite, public Thing  {
    public:
        static const int BUILDINGSEGMENT_SIZE = 15;

        BuildingSegment(SDL_Renderer* renderer);

        ThingType getType() const { return BUILDING; };

        void render(SDL_Rect* rect);
};

class BuildingStack : public std::list<Thing*>, public Thing {
    public:
        static const int MAX_SEGMENTS = 8;

        BuildingStack (SDL_Renderer* renderer);

        virtual ThingType getType() const { return STACK; };

        void grow();

        void shrink();

        void render(SDL_Rect* rect);
};

static array<string,1> BUILDING_TEXTURE_FILES = {"assets/tiles/building/home_0.png"};

class Building : public Sprite, public Thing {
    private:
        int level = 0;
    public:
        static const int BUILDING_SIZE = 0;

        Building(SDL_Renderer* renderer);

        ThingType getType() const { return BUILDING; };

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_BUILDING_H_
