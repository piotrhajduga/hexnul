#ifndef	_HEXNUL_GAME_H_
#define	_HEXNUL_GAME_H_

#include "SDL.h"

#include "state.h"
#include "world.h"
#include "tile.h"
#include "toolbar.h"

#define COLORS 12

class Game {
    public:
        Game();

        int OnExecute();

        bool OnInit();

        void OnEvent(SDL_Event* event);

        void OnLoop();

        void OnRender();

        void OnCleanup();

        void OnClick(SDL_MouseButtonEvent* event);

        void OnMouseMove(SDL_MouseMotionEvent* event);
    private:
        static const int TOOLBAR_H = 80;
        const int FPS = 30;
        bool running;
        unsigned int ticks = 0;

        SDL_Window* display;
        SDL_Renderer* renderer;
        GameState state;
        GameWorld* world;
        Toolbar* toolbar;
};

#endif	/* _HEXNUL_GAME_H_ */
