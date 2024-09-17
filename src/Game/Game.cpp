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
}

int Game::run() {
    // Gestion des messages de la fenêtre
    // running = Window::processMessages();

    while (!windowGLFW.shouldClose()) {
        // Input
        processInput();

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
        renderer_tests.cameraMovement(FORWARD);
    if(windowGLFW.GetKey(GLFW_KEY_S))
        renderer_tests.cameraMovement(BACKWARD);
    if(windowGLFW.GetKey(GLFW_KEY_A))
        renderer_tests.cameraMovement(LEFT);
    if(windowGLFW.GetKey(GLFW_KEY_D))
        renderer_tests.cameraMovement(RIGHT);
    if (windowGLFW.GetKey(GLFW_KEY_E))
        renderer_tests.cameraMovement(UP);
    if (windowGLFW.GetKey(GLFW_KEY_Q))
        renderer_tests.cameraMovement(DOWN);
}