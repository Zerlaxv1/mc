//
// Created by ninod on 18/09/2024.
//

#include <iostream>
#include "Mesh.h"

Mesh::Mesh() = default;

void Mesh::setVariables(float *vertices, unsigned int *indices, unsigned int verticesCount, unsigned int indicesCount) {
    this->vertices = vertices;
    this->indices = indices;
    this->verticesCount = verticesCount;
    this->indicesCount = indicesCount;
    this->verticesSize = verticesCount * sizeof(float);
    this->indicesSize = indicesCount * sizeof(unsigned int);
}

void Mesh::setupMesh() {
    // unsigned int indicesArray[6] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3 // second triangle
    // };
    //
    // float verticesArray[180] = {
    //     // positions          // texture coords
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //
    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    // };
    //
    // this->verticesCount = 180;
    // this->verticesSize = 180 * sizeof(float);
    // this->indicesCount = 6;
    // this->indicesSize = 6 * sizeof(unsigned int);

    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error while passing vertices / indices to the buffer : " << err << std::endl;
    }
}
