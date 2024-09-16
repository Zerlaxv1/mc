//
// Created by Nino on 25/08/2024.
//

#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "World.h"
#include "../GlTries/glTests.h"
#include "../GlTries/TexturesAndTransformations.h"

Game::Game() {
    // Créer une instance de World
    world = World();
    world.generateFlatWorld();
}

int Game::run() {
    // create the renderer
    auto renderer_tests = TexturesAndTransformations();
    // Gestion des messages de la fenêtre
    // running = Window::processMessages();

    while (!windowGLFW.shouldClose()) {
        //inputs
        int key = windowGLFW.processInput();
        if(key != 0) {
            if (key == GLFW_KEY_ESCAPE) {
                windowGLFW.terminate();
                return 0;
            }
            if (key == GLFW_KEY_Z) {
                renderer_tests.cameraMovement(glm::vec3(0.0f, 0.0f, 0.1f));
            }
        }

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
