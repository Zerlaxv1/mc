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
    float chunkUpdateTimer = 0.0f;
    const float chunkUpdateInterval = 6.0f;
    
    while (!windowGLFW.shouldClose()) {

        // calcul deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("Statistiques");

        ImGui::Text("Echape pour libérer la souris");

        ImGui::Separator();

        ImGui::Text("Temps entre les frames : %.3f ms", deltaTime * 1000.0f);
        ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);

        ImGui::NewLine();

        ImGui::Text("FOV");
        ImGui::SliderFloat("##FOV", &world.sharedPropsEngine.fov, 1.0f, 180.0f);

        ImGui::NewLine();

        ImGui::Text("Camera Position");
        ImGui::InputFloat3("##CameraPosition", &world.sharedPropsEngine.cameraPos.x);

        ImGui::NewLine();

        ImGui::Text("Camera Rotation");

        ImGui::NewLine();

        ImGui::Text("Camera Speed");
        ImGui::SliderFloat("##Camera Speed", &world.sharedPropsGame.cameraSpeed, 0.1f, 10.0f);
        ImGui::End();

        // Input
        processInput();

        // Rendering
        world.render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Map update
        chunkUpdateTimer += deltaTime;
        if (chunkUpdateTimer >= chunkUpdateInterval) {
            world.updateLoadedChunks();
            chunkUpdateTimer = 0.0f;
        }

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
    bool static lastStatusEscKey = false;
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

void Game::stop() {
    glfwSetWindowShouldClose(windowGLFW.window, true);
}
