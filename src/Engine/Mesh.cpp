//
// Created by ninod on 18/09/2024.
//

#include <iostream>
#include "Mesh.h"

Mesh::Mesh() {
    this->vertices = nullptr;
    this->indices = nullptr;
    this->verticesCount = 0;
    this->indicesCount = 0;
    this->verticesSize = 0;
    this->indicesSize = 0;
}

Mesh::Mesh(float *vertices, unsigned int *indices, unsigned int verticesCount, unsigned int indicesCount) {
    setVariables(vertices, indices, verticesCount, indicesCount);
}

void Mesh::setVariables(float *vertices, unsigned int *indices, unsigned int verticesCount, unsigned int indicesCount) {
    this->vertices = vertices;
    this->indices = indices;
    this->verticesCount = verticesCount;
    this->indicesCount = indicesCount;
    this->verticesSize = verticesCount * sizeof(float);
    this->indicesSize = indicesCount * sizeof(unsigned int);
}

void Mesh::setupMesh() {

    if(vertices == nullptr || indices == nullptr) {
        std::cerr << "Mesh has not been init" << std::endl;
        return;
    }

    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error while passing vertices / indices to the buffer : " << err << std::endl;
    }
}

float* Mesh::getVertices() {
    return this->vertices;
}

unsigned int*Mesh::getIndices() {
    return this->indices;
}
