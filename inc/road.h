#ifndef _HEXNUL_ROAD_THING_H_
#define _HEXNUL_ROAD_THING_H_

#include <map>
#include <unordered_map>

#include "SDL.h"

#include "constants.h"
#include "direction.h"
#include "worldstate.h"
#include "thing.h"

using namespace std;

typedef struct {
    Direction dir = TOPLEFT;
    Sprite* sprite;
    bool isVisible = false;
} RoadSegment;

class RoadNode : public Thing {
    public:
        const unsigned short int travelCost = 0xff;

        RoadNode(SDL_Renderer* renderer);
        virtual ~RoadNode();

        void render(SDL_Rect* rect);

        void setSegmentVisible(Direction dir);
        void setSegmentVisible(Direction dir, bool cond);

        virtual bool isVisible();

        bool isPassable() { return true; }
        int getMoveCost() { return 5; }
    protected:
        const char* SEGMENTS[6] = {
            TEXTURE_ROAD_TL,
            TEXTURE_ROAD_TR,
            TEXTURE_ROAD_R,
            TEXTURE_ROAD_BR,
            TEXTURE_ROAD_BL,
            TEXTURE_ROAD_L,
        };

        int getVisibleCount();

    private:
        map<Direction, RoadSegment> segments;

        int visibleCount = 0;
};

class Road : public RoadNode, public Sprite {
    public:
        Road(SDL_Renderer* renderer);

        virtual ThingType getType() const {
            return ROAD;
        }

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_ROAD_THING_H_
