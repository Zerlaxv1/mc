//
// Created by Nino on 25/08/2024.
//

#include "Game.h"

#include <GL/glew.h>
#include <windows.h>
#include <iostream>
#include "glTests.h"
#include "World.h"
#include "../Engine/Window.h"

void Game::initOpenGL() {
    dc = GetDC(this->window);
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    int format = ChoosePixelFormat(dc, &pfd);
    SetPixelFormat(dc, format, &pfd);
    glrc = wglCreateContext(dc);
    wglMakeCurrent(dc, glrc);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        exit(-1);
    }
}

Game::Game() {
    dc = nullptr;
    glrc = nullptr;

    // Create a window
    window = windowCreator.getHandle();

    // Initialize OpenGL
    initOpenGL();
}

Game::~Game() {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glrc);
    ReleaseDC(window, dc);
    delete window;
}

int Game::run() {
    // Créer une instance de World
    world = World();
    world.generateFlatWorld();

    glTests gl = glTests();

    while (running) {
        // Gestion des messages de la fenêtre
        running = Window::processMessages();

        // Effacer l'écran
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendre le monde
        // world.render();
        gl.renderTest();

        // Afficher le rendu
        SwapBuffers(dc);
    }

    return 0;
}
