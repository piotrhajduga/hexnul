#ifndef	_HEXNUL_GAME_THING_H_
#define	_HEXNUL_GAME_THING_H_

#include <unordered_map>
#include <functional>

#include "SDL.h"
#include "utils.h"
#include "thing.h"
#include "building.h"
#include "road.h"
#include "thingstack.h"

using namespace std;

typedef function<Thing*(SDL_Renderer*)> ThingTypeCreator;
typedef unordered_map<ThingType, ThingTypeCreator> ThingTypeMap;

class ThingFactory {
    private:
        SDL_Renderer* renderer;

    protected:
        ThingTypeMap types = {
            {STACK,
                [](SDL_Renderer* renderer) {
                    Utils::log(DEBUG, "Create ThingStack");
                    return new ThingStack(renderer);
                }},
            {BUILDING,
                [](SDL_Renderer* renderer) {
                    Utils::log(DEBUG, "Create BuildingSegment");
                    return new BuildingSegment(
                            renderer, "assets/tiles/building.png", 8);
                }},
            {ROAD,
                [](SDL_Renderer* renderer) {
                    Utils::log(DEBUG, "Create Road");
                    return new Road(renderer);
                }},
        };

    public:
        ThingFactory(SDL_Renderer* renderer);

        Thing* create(ThingType type);
};
#endif	/* _HEXNUL_GAME_THING_H_ */
