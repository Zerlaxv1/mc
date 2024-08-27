//
// Created by Nino on 25/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include "World.h"
#include "../Engine/Window.h"


class Game {
public:
    Game();
    ~Game();
    int run();

private:
    HWND windowHandle;
    HDC dc;
    HGLRC glrc;
    World world;
    bool running = true;
    Window window;
};



#endif //GAME_H
