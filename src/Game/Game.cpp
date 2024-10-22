//
// Created by Nino on 25/08/2024.
//

#include <GL/glew.h>
#include "Game.h"
#include <GLFW/glfw3.h>
#include "World.h"

Game::Game() {
//    world.generateFlatWorld();

    glfwSetWindowUserPointer(windowGLFW.window, this);
}

int Game::run() {
    while (!windowGLFW.shouldClose()) {
        // Input
        processInput();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Rendering
        world.render();

        // Swap buffers
        glfwSwapBuffers(windowGLFW.window);
        glfwPollEvents();
    }

    windowGLFW.terminate();
    return 0;
}

Game::~Game() = default;

void Game::processInput() {
    // Gestion des inputs
    if(windowGLFW.GetKey(GLFW_KEY_ESCAPE))
        windowGLFW.CloseWindow();
    if(windowGLFW.GetKey(GLFW_KEY_W))
        world.ProcessKeyboard(FORWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_S))
        world.ProcessKeyboard(BACKWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_A))
        world.ProcessKeyboard(LEFT, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_D))
        world.ProcessKeyboard(RIGHT, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_SPACE))
        world.ProcessKeyboard(UP, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_LEFT_SHIFT))
        world.ProcessKeyboard(DOWN , deltaTime);
}

void Game::processMouseMovement(double xpos, double ypos) {
    // constrainPitch : inverser haut et bas
    world.ProcessMouseMovement(xpos, ypos, true);
}

void Game::setWindowSize(int i, int i1) {
    world.setAspectRatio(i, i1);
}
