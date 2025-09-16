//
// Created by Nino on 25/08/2024.
//

#pragma once

#include <GL/glew.h>
#include "Renderer/Window/Window.h"
#include <windows.h>
#include "World/World.h"
#include "World/ChunkManager/Chunk/Block.h"
#include "World/ChunkManager/Chunk/Blocks.h"

class Game {
public:
    Game();
    ~Game();

    int run();
    void processInput();
    void processMouseMovement(double xpos, double ypos);
    void setWindowSize(int i, int i1);
    void toggleMouseLock();

    void stop();

private:
    Window windowGLFW;
    World world;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    bool cameraLocked;
    void imguiFrame();
};
