#ifndef _HEXNUL_ROAD_THING_H_
#define _HEXNUL_ROAD_THING_H_

#include <map>
#include <unordered_map>

#include "SDL.h"

#include "direction.h"
#include "state.h"
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

        bool isVisible();
    protected:
        const char* SEGMENTS[6] = {
            "assets/tiles/road_tl.png",
            "assets/tiles/road_tr.png",
            "assets/tiles/road_r.png",
            "assets/tiles/road_br.png",
            "assets/tiles/road_bl.png",
            "assets/tiles/road_l.png",
        };

        int getVisibleCount();

    private:
        map<Direction, RoadSegment> segments;

        int visibleCount = 0;
};

class Road : public RoadNode, public Sprite {
    protected:
        const char* ROAD_CENTER = "assets/tiles/road_c.png";

    public:
        Road(SDL_Renderer* renderer);

        virtual ThingType getType() const {
            return ROAD;
        }

        bool isVisible();

        void render(SDL_Rect* rect);
};

#endif //_HEXNUL_ROAD_THING_H_
