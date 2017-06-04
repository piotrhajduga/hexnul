#ifndef	_HEXNUL_THING_FACTORY_H_
#define	_HEXNUL_THING_FACTORY_H_

#include <string>
#include <unordered_map>
#include "thing.h"

using namespace std;

typedef unordered_map<string, pair<string, int>> ThingTypeMap;

class ThingFactory {
    private:
        SDL_Renderer* renderer;

    protected:
        ThingTypeMap types = {
            {"BUILDING", {"building.png", 8}},
        };

    public:
        ThingFactory(SDL_Renderer* irenderer) {
            renderer = irenderer;
        }

        Thing* create(string type) {
            ThingTypeMap::iterator it = types.find(type);
            if (it==types.end()) {
                return NULL;
            } else {
                return new Thing(renderer, it->second.first.c_str(), it->second.second);
            }
        }
};

#endif	/* _HEXNUL_THING_FACTORY_H_ */
