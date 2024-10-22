//
// Created by ninod on 18/09/2024.
//

#include <iostream>
#include "Mesh.h"

Mesh::Mesh() {
    this->vertices = std::vector<float>();
    this->indices = std::vector<unsigned int>();
}

void Mesh::setupMesh() {

    if(vertices.empty() || indices.empty()) {
        std::cerr << "Mesh has not been init" << std::endl;
        return;
    }

    unsigned int verticesSize = vertices.size() * sizeof(float);
    unsigned int indicesSize = indices.size() * sizeof(unsigned int);

    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error while passing vertices / indices to the buffer : " << err << std::endl;
    }
}

Mesh Mesh::CombineMeshs(std::vector<Mesh> meshes) {
    std::vector<float> combinedVertices;
    std::vector<unsigned int> combinedIndices;

    unsigned int indexOffset = 0;

    for (auto& mesh : meshes) {
        const auto& vertices = mesh.getVertices();
        const auto& indices = mesh.getIndices();

        combinedVertices.insert(combinedVertices.end(), vertices.begin(), vertices.end());

        for (unsigned int i = 0; i < mesh.getIndices().size(); ++i) {
            combinedIndices.push_back(indices[i] + indexOffset);
        }

        indexOffset += mesh.getVertices().size() / 6; // Assuming each vertex has 6 attributes (3 for position, 2 for texture, 1 for texture index)
    }

    return Mesh(combinedVertices, combinedIndices);
}