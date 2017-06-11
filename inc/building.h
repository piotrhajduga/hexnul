#ifndef	_HEXNUL_BUILDING_H_
#define	_HEXNUL_BUILDING_H_

#include <map>
#include <string>
#include <list>
#include "SDL.h"

#include "utils.h"
#include "road.h"
#include "sprite.h"
#include "thing.h"

using namespace std;

class BuildingWithLevel : public RoadNode {
    private:
        static map<int, Sprite*> levels;
        int level = 0;

        Sprite* sprite;

    protected:
        void update();

        const int MAXLEVEL = 1;
        const int MAX_VISIBLE_SEGMENTS = 1;
        const char* LEVEL_TEXTURES[2] = {
            "assets/tiles/building/home_0.png",
            "assets/tiles/building/home_1.png",
        };

    public:
        static void deleteLevels();

        BuildingWithLevel(SDL_Renderer* renderer);
        BuildingWithLevel(SDL_Renderer* renderer, int initialLevel);
        virtual ~BuildingWithLevel();

        int getLevel();

        Sprite* getLevel(int level);

        int incLevel();

        void setLevel(int level);

        void render(SDL_Rect* rect);
        
};

static string BUILDINGSEGMENT_TEXTURE_FILE = "assets/tiles/building.png";

class BuildingSegment : public Sprite, public Thing  {
    public:
        static const int BUILDINGSEGMENT_SIZE = 10;

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
    public:
        static const int BUILDING_SIZE = 0;

        Building(SDL_Renderer* renderer);

        ThingType getType() const { return BUILDING; };

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_BUILDING_H_
