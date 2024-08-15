#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "Shader.h"
#include "../Game/World.h"

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

LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam) {
    LRESULT result = 0;
    switch(msg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
        default: { result = DefWindowProc(window, msg, wparam, lparam); }
    }
    return result;
}

int main() {
    // Créer une fenêtre
    WNDCLASSEX c = {0};
    c.cbSize = sizeof(c);
    c.lpfnWndProc = window_proc;
    c.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    c.lpszClassName = "minecraft";
    c.hInstance = GetModuleHandle(nullptr);
    RegisterClassEx(&c);

    HWND window = CreateWindow("minecraft", "super minecraft clone 3000", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    HDC dc;
    HGLRC glrc;
    initOpenGL(window, dc, glrc);

    // Vertex shader
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
    )";

    // Fragment shader
    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 1.0, 0.2, 1.0);
    }
    )";

    // Compile et lie les shaders
    GLuint shaderProgram = Shader::createProgram(vertexShaderSource, fragmentShaderSource);

    // Créer une instance de World
    World world;

    // Ajouter un bloc à la position (0, 0, 0) dans le chunk (1, 0, 0)
    world.activateBlock(0, 0, 0, 0, 0, 0);
    world.activateBlock(1, 0, 0, 1, 0, 0);
    world.activateBlock(0, 1, 0, 0, 1, 0);
    world.activateBlock(0, 0, 1, 0, 0, 1);

    MSG msg;

    // Boucle principale
    while(true) {
        while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
            if(msg.message == WM_QUIT) { return 0; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.1f, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Utilise le shader program
        glUseProgram(shaderProgram);

        // Rendre le monde
        World::renderWorld(world);

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