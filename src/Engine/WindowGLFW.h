//
// Created by ninod on 16/09/2024.
//

#ifndef OPENGL_TESTS_WINDOWGLFW_H
#define OPENGL_TESTS_WINDOWGLFW_H

#include <GLFW/glfw3.h>

class WindowGLFW {
public:
    WindowGLFW();
    ~WindowGLFW();

    GLFWwindow* window;

    void createWindow(const char* title, int width, int height);
    void terminate();
    int processInput();
    bool shouldClose() const;
    bool GetKey(int key);
    void CloseWindow();
};


#endif //OPENGL_TESTS_WINDOWGLFW_H
