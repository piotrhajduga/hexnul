/*
 * "Ballfield"
 *
 *   (C) David Olofson <david@olofson.net>, 2002
 *
 * This software is released under the terms of the GPL.
 *
 * Contact author for permission if you want to use this
 * software, or work derived from it, under other terms.
 */

#ifndef	_HEXNUL_H_
#define	_HEXNUL_H_

#include "SDL.h"

#define WIN_W 640
#define WIN_H 480
#define RECT_H 32
#define RECT_W 40
#define RECT_W_OFFSET 20
#define BOARD_OFFSET_X 10
#define BOARD_OFFSET_Y 16

class HexNullApp {
    private:
        bool running;

        SDL_Window* display;
        SDL_Renderer* renderer;

        void drawHexs(int rows, int cols);

    public:
        HexNullApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* event);

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif	/* _HEXNUL_H_ */
