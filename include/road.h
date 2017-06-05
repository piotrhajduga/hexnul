#ifndef _HEXNUL_ROAD_THING_H_
#define _HEXNUL_ROAD_THING_H_

#include <map>
#include <unordered_map>
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
        static constexpr const char* SEGMENTS[6] = {
            "assets/tiles/road_tl.png",
            "assets/tiles/road_tr.png",
            "assets/tiles/road_l.png",
            "assets/tiles/road_r.png",
            "assets/tiles/road_bl.png",
            "assets/tiles/road_br.png",
        };

    public:
        Road(SDL_Renderer* renderer) : Thing(renderer) {
            initSegmentSprite(TOPLEFT);
            initSegmentSprite(TOPRIGHT);
            initSegmentSprite(LEFT);
            initSegmentSprite(RIGHT);
            initSegmentSprite(BOTTOMLEFT);
            initSegmentSprite(BOTTOMRIGHT);
        }
        ~Road() {
            for (auto it=segments.begin();it!=segments.end();++it) {
                if (it->second.sprite != NULL) {
                    delete it->second.sprite;
                }
            }
        }

        void setVisible(RoadDir dir) {
            segments[dir].isVisible = true;
        }

        void render(SDL_Rect* rect) {
            for (auto it=segments.begin();it!=segments.end();++it) {
                if (it->second.isVisible) {
                    it->second.sprite->render(rect);
                }
            }
        }

    private:
        map<RoadDir, RoadSegment> segments;

        void initSegmentSprite(RoadDir dir) {
            segments[dir].sprite = new Sprite(renderer, SEGMENTS[dir]);
        }
};

#endif //_HEXNUL_ROAD_THING_H_
