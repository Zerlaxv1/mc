//
// Created by ninod on 16/09/2024.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowGLFW.h"

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* _, int width, int height) {
    glViewport(0, 0, width, height);
}


WindowGLFW::WindowGLFW() {
    window = nullptr;

    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //macOS:
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    createWindow("super mc clone 3000", 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        exit(-1);
    }
}

WindowGLFW::~WindowGLFW() {
    glfwTerminate();
}

void WindowGLFW::createWindow(const char *title, int width, int height) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW windowGLFW" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
}

void WindowGLFW::terminate() {
    glfwTerminate();
}

void WindowGLFW::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool WindowGLFW::shouldClose() {
    return glfwWindowShouldClose(window);
}