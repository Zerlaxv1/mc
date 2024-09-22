//
// Created by ninod on 16/09/2024.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "../Game/Game.h"

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* _, int width, int height, Game* game) {
    glViewport(0, 0, width, height);
    game->setWindowSize(width, height);
}

void framebuffer_size_callback_glfw([[maybe_unused]] GLFWwindow* window, int width, int height) {
    // Récupérer le pointeur vers l'instance de Game
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) {
        framebuffer_size_callback(window, width, height, game);
    }
}

void mouse_callback(GLFWwindow* _, double xpos, double ypos, Game* game)
{
    static bool firstMouse = true;
    static float lastX = 400, lastY = 300;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    game->processMouseMovement(xoffset, yoffset);
}

void mouse_callback_glfw(GLFWwindow* window, double xpos, double ypos)
{
    // Récupérer le pointeur vers l'instance de Game
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) {
        mouse_callback(window, xpos, ypos, game);
    }
}

Window::Window() {
    window = nullptr;

    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    createWindow("super mc clone 3000", width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_glfw);
    glfwSetCursorPosCallback(window, mouse_callback_glfw);
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        exit(-1);
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    framebuffer_size_callback_glfw(window, width, height);
}

Window::~Window() {
    glfwTerminate();
}

void Window::createWindow(const char *title, int width, int height) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
}

void Window::terminate() {
    glfwTerminate();
}

bool Window::GetKey(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Window::CloseWindow() {
    glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}