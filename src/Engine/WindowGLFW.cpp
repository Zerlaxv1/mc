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

int WindowGLFW::processInput()
{
    // const float cameraSpeed = 0.05f; // adjust accordingly
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        return GLFW_KEY_Z;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        return GLFW_KEY_S;
        // cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        return GLFW_KEY_Q;
        // cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        return GLFW_KEY_D;
        // cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

bool WindowGLFW::GetKey(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void WindowGLFW::CloseWindow() {
    glfwSetWindowShouldClose(window, true);
}

bool WindowGLFW::shouldClose() const {
    return glfwWindowShouldClose(window);
}