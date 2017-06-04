#ifndef	_HEXNUL_GAME_THING_H_
#define	_HEXNUL_GAME_THING_H_

#include <string>
#include <unordered_map>

#include "SDL.h"
#include "tile.h"

using namespace std;

class Thing : public Sprite {
    public:
        int height = 0;
        Thing(SDL_Renderer* renderer, const char *textureFile)
            : Sprite (renderer, textureFile) {}
        Thing(SDL_Renderer* renderer, const char *textureFile, int iheight)
            : Sprite (renderer, textureFile) {
                height = iheight;
            }
        virtual ~Thing() {};
};

typedef unordered_map<string, pair<string, int>> ThingTypeMap;

class ThingFactory {
    private:
        SDL_Renderer* renderer;

    protected:
        ThingTypeMap types = {
            {"BUILDING", {"assets/tiles/building.png", 8}},
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
#endif	/* _HEXNUL_GAME_THING_H_ */
