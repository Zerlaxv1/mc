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
    ImGuiIO& io = ImGui::GetIO();
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
        ImGui::ShowDemoWindow(); // Show demo window! :)

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
    // Gestion des inputs
    if(windowGLFW.GetKey(GLFW_KEY_ESCAPE))
        windowGLFW.CloseWindow();
    if(windowGLFW.GetKey(GLFW_KEY_W))
        world.ProcessKeyboard(FORWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_S))
        world.ProcessKeyboard(BACKWARD, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_A))
        world.ProcessKeyboard(LEFT, deltaTime);
    if(windowGLFW.GetKey(GLFW_KEY_D))
        world.ProcessKeyboard(RIGHT, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_SPACE))
        world.ProcessKeyboard(UP, deltaTime);
    if (windowGLFW.GetKey(GLFW_KEY_LEFT_SHIFT))
        world.ProcessKeyboard(DOWN , deltaTime);
}

void Game::processMouseMovement(double xpos, double ypos) {
    // constrainPitch : inverser haut et bas
    world.ProcessMouseMovement(xpos, ypos, true);
}

void Game::setWindowSize(int i, int i1) {
    world.setAspectRatio(i, i1);
}
