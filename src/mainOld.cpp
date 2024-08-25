#include <iostream>
#include <Windows.h>
#include "../cmake-build-release/vcpkg_installed/x64-windows/include/GL/glew.h"
#include "../cmake-build-release/vcpkg_installed/x64-windows/include/GL/GL.h"
#include "Engine/Shader.h"
#include "Game/World.h"
#include "Engine/Window.h"
#include "Game/glTests.h"

// Fonction pour initialiser OpenGL
void initOpenGL(HWND window, HDC& dc, HGLRC& glrc) {
    dc = GetDC(window);
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

World generateFlatWorld() {
    World world;
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            world.activateBlock(0, 0, 0, x, 0, z);
        }
    }
    return world;
}

int main(int argc, char* argv[]) {

    // Créer une fenêtre
    Window windo = Window();
    HWND window = windo.getHandle();

    // Initialiser OpenGL
    HDC dc;
    HGLRC glrc;
    initOpenGL(window, dc, glrc);

    // Créer une instance de World
    World world = generateFlatWorld();

    MSG msg;

    glTests gl = glTests();

    // Utilise le shader program

    // Boucle principale
    while(true) {
        // Gestion des messages de la fenêtre
        while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
            if(msg.message == WM_QUIT) { return 0; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // Effacer l'écran
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendre le monde
        // World::renderWorld(world, shaderProgram);
        gl.renderTest();

        // Afficher le rendu
        SwapBuffers(dc);
    }

    // Cleanup
    glDeleteProgram(shaderProgram);
    wglDeleteContext(glrc);
    ReleaseDC(window, dc);
    DestroyWindow(window);
    UnregisterClass("minecraft", GetModuleHandle(nullptr));

    return 0;
}