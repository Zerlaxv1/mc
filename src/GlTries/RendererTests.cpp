//
// Created by Nino on 01/09/2024.
//

#include "RendererTests.h"

RendererTests::RendererTests() :
        shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
        camera(glm::vec3(0.0f, 0.0f, 3.0f)),
        texture("./Resources/Textures/dirt.png"),
        renderer(&mesh, shader, camera, texture)
{
    float verticesArrayElements[] = {
            // positions         // texture coords
            // Front face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 0
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 1
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // 2
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // 3

            // Back face
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // 4
            0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  // 5
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // 6
            -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // 7

            // Left face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 8 (same as 0)
            -0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  // 9 (same as 3)
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // 10
            -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  // 11 (same as 4)

            // Right face
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 12 (same as 1)
            0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  // 13 (same as 2)
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // 14 (same as 6)
            0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  // 15 (same as 5)

            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // 16 (same as 0)
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // 17 (same as 1)
            0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  // 18 (same as 5)
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // 19 (same as 4)

            // Top face
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // 20 (same as 3)
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // 21 (same as 2)
            0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  // 22 (same as 6)
            -0.5f,  0.5f,  0.5f, 0.0f, 0.0f   // 23 (same as 7)
    };

    unsigned int indicesArrayElements[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            0, 9, 10,
            10, 11, 0,

            // Right face
            12, 13, 14,
            14, 15, 12,

            // Bottom face
            16, 17, 18,
            18, 19, 16,

            // Top face
            20, 21, 22,
            22, 23, 20
    };


    mesh.setVariables(verticesArrayElements, indicesArrayElements, sizeof(verticesArrayElements) / sizeof(float), sizeof(indicesArrayElements) / sizeof(unsigned int));
    renderer.setAspectRatio(800, 600);
    renderer.init();
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
