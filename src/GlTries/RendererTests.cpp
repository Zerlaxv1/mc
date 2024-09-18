//
// Created by Nino on 01/09/2024.
//


#include "RendererTests.h"
#include "../Engine/Renderer.h"

RendererTests::RendererTests() {
    float vertices[] = {
        // positions            // colors
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   // top left
   };
    unsigned int indices[] = {
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
    };
    renderer.copyVerticesData(vertices, sizeof(vertices));
    renderer.copyIndicesData(indices, sizeof(indices));
}

void RendererTests::run() {
    renderer.draw();
}
