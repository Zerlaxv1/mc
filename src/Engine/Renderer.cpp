//
// Created by Nino on 01/09/2024.
//

#include "Renderer.h"

#include <iostream>
#include <GL/glew.h>

void Renderer::init() {
    vertices = 0;
    indices = 0;
    VBO, VAO, EBO = 0;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Renderer::Renderer() {
    init();
}

Renderer::Renderer(float verticesArg[], int size , GLuint indicesArg[], int size2) {
    init();
    copyVerticesData(verticesArg, size);
    copyIndicesData(indicesArg, size2);
}

Renderer::~Renderer() = default;

void Renderer::draw() {
    shader.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::copyVerticesData(float verticesarg[], int size) {
    glBufferData(GL_ARRAY_BUFFER, size, verticesarg, GL_STATIC_DRAW);
}

void Renderer::copyIndicesData(unsigned int indicesArg[], int size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesArg, GL_STATIC_DRAW);
}