#ifndef	_HEXNUL_GAME_THING_H_
#define	_HEXNUL_GAME_THING_H_

#include <string>
#include <unordered_map>

#include "SDL.h"
#include "base_thing.h"
#include "building.h"
#include "thingstack.h"

using namespace std;

typedef struct {
    const char* textureFile;
    int height;
} ThingTypeData;

typedef unordered_map<ThingType, ThingTypeData> ThingTypeMap;

class ThingFactory {
    private:
        SDL_Renderer* renderer;

    protected:
        ThingTypeMap types = {
            {STACK, {"", 0}},
            {BUILDING, {"assets/tiles/building.png", 8}},
        };

    public:
        ThingFactory(SDL_Renderer* irenderer) {
            renderer = irenderer;
        }

        Thing* create(ThingType type) {
            try {
                ThingTypeData typeData = types.at(type);
                return create(type, typeData);
            } catch (const out_of_range& oor) {
                return NULL;
            }
        }

        Thing* create(ThingType type, ThingTypeData typeData) {
            switch (type) {
                case STACK:
                    return new ThingStack(renderer);
                case BUILDING:
                    return new BuildingSegment(renderer, typeData.textureFile, typeData.height);
                default:
                    return NULL;
            }
        }
};
#endif	/* _HEXNUL_GAME_THING_H_ */
