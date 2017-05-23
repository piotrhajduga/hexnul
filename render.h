#ifndef	_HEXNUL_GAME_RENDER_H_
#define	_HEXNUL_GAME_RENDER_H_

#include "SDL.h"
#include "state.h"

#define HEX_H 36
#define HEX_W 48

class GameRender {
    public:
        GameRender(
                SDL_Renderer* renderer,
                GameState* state
                );
        ~GameRender();
        void render();
        void drawHexs(int cols, int rows);
        void drawHex(int col, int row);
    private:
        SDL_Renderer* renderer;
        GameState* state;
};

#endif	/* _HEXNUL_GAME_RENDER_H_ */
