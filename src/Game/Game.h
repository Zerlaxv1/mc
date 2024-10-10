//
// Created by Nino on 25/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "../Engine/Window.h"
#include <windows.h>
#include "World.h"
#include "../GlTries/RendererTests.h"
#include "Blocks/Block.h"
#include "Blocks/Blocks.h"

class Game {
public:
    Game();
    ~Game();

    int run();
    void processInput();
    void processMouseMovement(double xpos, double ypos);
    void setWindowSize(int i, int i1);
private:
    Window windowGLFW;
    World world;
    Blocks blocks;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};



#endif //GAME_H
