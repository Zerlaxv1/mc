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

class Game {
public:
    Game();
    ~Game();
    int run();

    void processInput();
    void processMouseMovement(double xpos, double ypos);
private:
    World world;
    Window windowGLFW;
    RendererTests renderer_tests;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};



#endif //GAME_H
