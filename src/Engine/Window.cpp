//
// Created by Nino on 20/08/2024.
//

#include <windows.h>
#include "Window.h"

HWND window;

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

void Window::create(LPCSTR jsp, LPCSTR name) {
    window = CreateWindow(jsp, name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
}

HWND Window::getHandle() {
    if (window == nullptr) {
        create("minecraft", "super minecraft clone 3000");
    }
    return window;
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
