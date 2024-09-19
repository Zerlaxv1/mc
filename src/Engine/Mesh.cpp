//
// Created by ninod on 18/09/2024.
//

#include <iostream>
#include "Mesh.h"

Mesh::Mesh(float *vertices, unsigned int *indices, unsigned int verticesCount, unsigned int indicesCount) {
    this->vertices = vertices;
    this->indices = indices;
    this->verticesCount = verticesCount;
    this->indicesCount = indicesCount;
    this->verticesSize = verticesCount * sizeof(float);
    this->indicesSize = indicesCount * sizeof(unsigned int);

    // Affichage pour le débogage
    std::cout << "Vertices : ";
    for (int i = 0; i < verticesCount;++i) {
        std::cout << vertices[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Indices : ";
    for (int i = 0; i < indicesCount;++i) {
        std::cout << indices[i] << std::endl;
    }
    std::cout << std::endl;
}

void Mesh::setupMesh() {
    //print vertices
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, indices, GL_STATIC_DRAW);
    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error while passing vertices / indices to the buffer : " << err << std::endl;
    }
}
