#ifndef	_HEXNUL_H_
#define	_HEXNUL_H_

#include "SDL.h"
#include "world.h"

#define WIN_W 640
#define WIN_H 480
#define BOARD_OFFSET_X 0
#define BOARD_OFFSET_Y 0
#define COLORS 12

class HexNullApp {
    public:
        HexNullApp();

        int OnExecute();

        bool OnInit();

        void OnEvent(SDL_Event* event);

        void OnLoop();

        void OnRender();

        void OnCleanup();

        void OnClick(SDL_MouseButtonEvent* event);
    private:
        bool running;

        SDL_Window* display;
        SDL_Renderer* renderer;
        GameWorld* world;

        void drawHexs(int cols, int rows);
        void drawHex(int col, int row);
        void drawHex(SDL_Point offset);
};

#endif	/* _HEXNUL_H_ */
