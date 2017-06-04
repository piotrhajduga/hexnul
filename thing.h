#ifndef	_HEXNUL_GAME_THING_H_
#define	_HEXNUL_GAME_THING_H_

#include "SDL.h"
#include "tile.h"

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

#endif	/* _HEXNUL_GAME_THING_H_ */
