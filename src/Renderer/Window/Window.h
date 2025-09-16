//
// Created by ninod on 16/09/2024.
//

#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();

    GLFWwindow* window;

    void createWindow(const char* title, int width, int height);
    void terminate();
    int processInput();
    bool shouldClose() const;
    bool GetKey(int key);
    void CloseWindow();

    int width = 800;
    int height = 600;
private:
    float lastX = 400, lastY = 300;
    bool firstMouse = true;
};
