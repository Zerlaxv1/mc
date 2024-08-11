#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "Shader.h"

LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
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

int main()
{
    // Create window
    WNDCLASSEX c = {0};
    c.cbSize = sizeof(c);
    c.lpfnWndProc = window_proc;
    c.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    c.lpszClassName = "minecraft";
    c.hInstance = GetModuleHandle(nullptr);
    RegisterClassEx(&c);

    HWND window = CreateWindow("minecraft", "super minecraft clone 3000", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    HDC dc = GetDC(window);
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    int format = ChoosePixelFormat(dc, &pfd);
    SetPixelFormat(dc, format, &pfd);
    HGLRC glrc = wglCreateContext(dc);
    wglMakeCurrent(dc, glrc);

    //OpenGL extensions loader
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        return -1;
    }

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

    // Crée un triangle
    float vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        // Bind le VAO et dessine le triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SwapBuffers(dc);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    wglDeleteContext(glrc);
    ReleaseDC(window, dc);
    DestroyWindow(window);
    UnregisterClass("minecraft", GetModuleHandle(nullptr));

    return 0;
}