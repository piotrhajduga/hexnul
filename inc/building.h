#ifndef	_HEXNUL_BUILDING_H_
#define	_HEXNUL_BUILDING_H_

#include <map>
#include <string>
#include <list>
#include "SDL.h"

#include "constants.h"
#include "utils.h"
#include "road.h"
#include "sprite.h"
#include "thing.h"

using namespace std;

struct BuildingLevelData {
    const char* textureFile;
    int height;
    bool visibleRoads;
};

class BuildingWithLevel : public RoadNode {
    private:
        static map<int, Sprite*> levels;
        int level = 0;
        Sprite* sprite;
        bool visibleRoads;

    protected:
        void update();

        const int MAXLEVEL = 2;
        const BuildingLevelData LEVELS[3] = {
            {TEXTURE_BUILDING_HOME_0, 0, false},
            {TEXTURE_BUILDING_HOME_1, 0, true},
            {TEXTURE_BUILDING_HOME_2, 12, true},
        };

    public:
        virtual bool isVisible();
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

class BuildingSegment : public Sprite, public Thing  {
    public:
        const int BUILDINGSEGMENT_SIZE = 10;

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

class Building : public Sprite, public Thing {
    public:
        const int BUILDING_SIZE = 0;

        Building(SDL_Renderer* renderer);

        ThingType getType() const { return BUILDING; };

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_BUILDING_H_
