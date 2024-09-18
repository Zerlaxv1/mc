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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
        renderer_tests.ProcessKeyboard(FORWARD);
    if(windowGLFW.GetKey(GLFW_KEY_S))
        renderer_tests.ProcessKeyboard(BACKWARD);
    if(windowGLFW.GetKey(GLFW_KEY_A))
        renderer_tests.ProcessKeyboard(LEFT);
    if(windowGLFW.GetKey(GLFW_KEY_D))
        renderer_tests.ProcessKeyboard(RIGHT);
    if (windowGLFW.GetKey(GLFW_KEY_SPACE))
        renderer_tests.ProcessKeyboard(UP);
    if (windowGLFW.GetKey(GLFW_KEY_LEFT_SHIFT))
        renderer_tests.ProcessKeyboard(DOWN);
}

void Game::processMouseMovement(double xpos, double ypos) {
    // constrainPitch : inverser haut et bas
    renderer_tests.ProcessMouseMovement(xpos, ypos, true);
}