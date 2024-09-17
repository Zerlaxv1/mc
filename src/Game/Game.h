//
// Created by Nino on 25/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "../Engine/WindowGLFW.h"
#include <windows.h>
#include "World.h"
#include "../GlTries/TexturesAndTransformations.h"


class Game {
public:
    Game();
    ~Game();
    int run();

    void processInput();
private:
    World world;
    WindowGLFW windowGLFW;
    TexturesAndTransformations renderer_tests;
};



#endif //GAME_H
