#ifndef _HEXNUL_ROAD_THING_H_
#define _HEXNUL_ROAD_THING_H_

#include <map>
#include <unordered_map>

#include "SDL.h"

#include "state.h"
#include "thing.h"

using namespace std;

typedef enum {
    TOPLEFT,TOPRIGHT,
    LEFT,RIGHT,
    BOTTOMLEFT,BOTTOMRIGHT,
} RoadDir;

typedef struct {
    RoadDir dir = TOPLEFT;
    Sprite* sprite;
    bool isVisible = false;
} RoadSegment;

class Road : public Thing {
    protected:
        const char* SEGMENTS[6] = {
            "assets/tiles/road_tl.png",
            "assets/tiles/road_tr.png",
            "assets/tiles/road_l.png",
            "assets/tiles/road_r.png",
            "assets/tiles/road_bl.png",
            "assets/tiles/road_br.png",
        };

    public:
        Road(SDL_Renderer* renderer);
        virtual ~Road();

        virtual ThingType getType() const {
            return ROAD;
        }

        void setVisible(RoadDir dir);

        void render(SDL_Rect* rect);

    private:
        map<RoadDir, RoadSegment> segments;

        void initSegmentSprite(RoadDir dir);
};

#endif //_HEXNUL_ROAD_THING_H_
