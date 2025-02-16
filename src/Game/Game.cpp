//
// Created by Nino on 25/08/2024.
//

#include <GL/glew.h>
#include "Game.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "World.h"

Game::Game() {
    // Initialize IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Initialize game
    Blocks::initialize();
    world.Init();

    // Initialize GLFW
    glfwSetWindowUserPointer(windowGLFW.window, this);

    // init imgui
    ImGui_ImplGlfw_InitForOpenGL(windowGLFW.window, true);
    ImGui_ImplOpenGL3_Init();
}

int Game::run() {
    while (!windowGLFW.shouldClose()) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Statistiques");

        // Affiche le nombre de FPS avec une décimale
        ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);

        // Fin de la fenêtre ImGui
        ImGui::End();


        // Input
        processInput();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Rendering
        world.render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(windowGLFW.window);
        glfwPollEvents();
    }

    windowGLFW.terminate();
    return 0;
}

Game::~Game() {
    // Shutdown ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Game::processInput() {
    // if the escape key is pressed for the first time, toggle the camera lock
    // if the escape key is pressed for the second time ignore it until it is released
    // if the escape key is released, allow it to be pressed again
    // this is to prevent the camera from being toggled multiple times when the key is held down

    // true = pressed, false = released
    bool static lastStatusEscKey;
    bool currentStatusEscKey = windowGLFW.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS;

    if (currentStatusEscKey && !lastStatusEscKey) {
        // esc pressed for the first time
        toggleMouseLock();
        world.toggleCameraLock();
        lastStatusEscKey = true;
    } else if (!currentStatusEscKey) {
        // esc released
        lastStatusEscKey = false;
    }

    if (windowGLFW.GetKey(GLFW_KEY_W) == GLFW_PRESS)
        world.ProcessKeyboard(FORWARD, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_S) == GLFW_PRESS)
        world.ProcessKeyboard(BACKWARD, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_A) == GLFW_PRESS)
        world.ProcessKeyboard(LEFT, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_D) == GLFW_PRESS)
        world.ProcessKeyboard(RIGHT, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        world.ProcessKeyboard(UP, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        world.ProcessKeyboard(DOWN, deltaTime);
}

void Game::processMouseMovement(double xpos, double ypos) {
    // constrainPitch : inverser haut et bas
    if (!cameraLocked)
        world.ProcessMouseMovement(xpos, ypos, true);
}

void Game::setWindowSize(int i, int i1) {
    world.setAspectRatio(i, i1);
}

void Game::toggleMouseLock() {
    if (glfwGetInputMode(windowGLFW.window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(windowGLFW.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(windowGLFW.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
