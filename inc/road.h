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

class Road : public Thing {
    protected:
        const char* CENTER = "assets/tiles/road_c.png";
        const char* SEGMENTS[6] = {
            "assets/tiles/road_tl.png",
            "assets/tiles/road_tr.png",
            "assets/tiles/road_r.png",
            "assets/tiles/road_br.png",
            "assets/tiles/road_bl.png",
            "assets/tiles/road_l.png",
        };

    public:
        Road(SDL_Renderer* renderer);
        virtual ~Road();

        virtual ThingType getType() const {
            return ROAD;
        }

        void setSegmentVisible(Direction dir);
        void setSegmentVisible(Direction dir, bool cond);

        void render(SDL_Rect* rect);

    private:
        Sprite* center;
        map<Direction, RoadSegment> segments;
};

#endif //_HEXNUL_ROAD_THING_H_
