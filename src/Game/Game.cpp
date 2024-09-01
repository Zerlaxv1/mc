//
// Created by Nino on 25/08/2024.
//

#include "Game.h"

#include <GL/glew.h>
#include <windows.h>
#include <iostream>
#include "World.h"
#include "../Engine/Window.h"

#include "../GlTries/glTests.h"
#include "../GlTries/RendererTests.h"

Game::Game() {
    dc = nullptr;
    glrc = nullptr;

    windowHandle = window.init(&dc, &glrc);
}

Game::~Game() {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(glrc);
    ReleaseDC(windowHandle, dc);
}

int Game::run() {
    // Créer une instance de World
    world = World();
    world.generateFlatWorld();

    // auto gl = glTests();
    auto renderer_tests = RendererTests();

    while (running) {
        // Gestion des messages de la fenêtre
        running = Window::processMessages();

        // Effacer l'écran
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendre le monde
        // world.render();
        // gl.renderTest();
        renderer_tests.run();

        // Afficher le rendu
        SwapBuffers(dc);
    }

    return 0;
}