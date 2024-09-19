//
// Created by Nino on 01/09/2024.
//

#include "RendererTests.h"

RendererTests::RendererTests() :
        mesh(verticesArray, indicesArray, sizeof(verticesArray) / sizeof(verticesArray[0]), sizeof(indicesArray) / sizeof(indicesArray[0])),
        shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
        camera(glm::vec3(0.0f, 0.0f, 3.0f)),
        texture("./Resources/Textures/dirt.png"),
        renderer(mesh, shader, camera, texture)
{
}

void RendererTests::render() {
    renderer.draw();
}

void RendererTests::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    renderer.ProcessKeyboard(movement, deltatime);
}

void RendererTests::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    renderer.ProcessMouseMovement(xpos, ypos, cond);
}

void RendererTests::setAspectRatio(int i, int i1) {
    renderer.setAspectRatio(i, i1);
}
