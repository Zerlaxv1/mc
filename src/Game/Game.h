//
// Created by Nino on 25/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "../Engine/WindowGLFW.h"
#include <windows.h>
#include "World.h"


class Game {
public:
    Game();
    ~Game();
    int run();

private:
    World world;
    WindowGLFW windowGLFW;
};



#endif //GAME_H
