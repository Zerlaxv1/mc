//
// Created by Nino on 20/08/2024.
//

#include <GL/glew.h>
#include <windows.h>
#include <iostream>
#include "Window.h"

LRESULT Window::window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam) {
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

Window::Window() {
    dc = nullptr;
    glrc = nullptr;
    window = nullptr;

    // Créer une fenêtre
    WNDCLASSEX c = {0};
    c.cbSize = sizeof(c);
    c.lpfnWndProc = window_proc;
    c.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    c.lpszClassName = "minecraft";
    c.hInstance = GetModuleHandle(nullptr);
    RegisterClassEx(&c);
}

Window::~Window() {
    DestroyWindow(window);
    UnregisterClass("minecraft", GetModuleHandle(nullptr));
}

void Window::createWindow(LPCSTR jsp, LPCSTR name) {
    window = CreateWindow(jsp, name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
}

bool Window::processMessages() {
    MSG msg;
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
        if(msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void Window::initOpenGL() {
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

HWND Window::init(HDC* dc, HGLRC* glrc) {
    createWindow("minecraft", "super minecraft clone 3000");

    initOpenGL();

    *dc = this->dc;
    *glrc = this->glrc;

    return window;
}
