//
// Created by Nino on 25/08/2024.
//

#include <GL/glew.h>
#include "Game.h"
#include <GLFW/glfw3.h>
#include "World.h"

Game::Game() {
    // Créer une instance de World
    world = World();
    world.generateFlatWorld();

    glfwSetWindowUserPointer(windowGLFW.window, this);
}

int Game::run() {
    // Gestion des messages de la fenêtre
    // running = Window::processMessages();

    while (!windowGLFW.shouldClose()) {
        // Input
        processInput();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Rendering
        renderer_tests.render();

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
        renderer_tests.ProcessKeyboard(FORWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_S))
        renderer_tests.ProcessKeyboard(BACKWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_A))
        renderer_tests.ProcessKeyboard(LEFT, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_D))
        renderer_tests.ProcessKeyboard(RIGHT, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_SPACE))
        renderer_tests.ProcessKeyboard(UP, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_LEFT_SHIFT))
        renderer_tests.ProcessKeyboard(DOWN , deltaTime);
}

void Game::processMouseMovement(double xpos, double ypos) {
    // constrainPitch : inverser haut et bas
    renderer_tests.ProcessMouseMovement(xpos, ypos, true);
}

void Game::setWindowSize(int i, int i1) {
    renderer_tests.setAspectRatio(i, i1);
}
