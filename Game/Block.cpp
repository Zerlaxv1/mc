//
// Created by Nino on 11/08/2024.
//

#include "Block.h"
#include <vector>
#include <GL/glew.h>

Block::Block() {
    isVisible = false;
}

void Block::generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float x, float y, float z) {
    // Sommets d'un cube
    GLfloat cubeVertices[] = {
        // Positions          // Normales
        x, y, z,              0.0f, 0.0f, -1.0f,
        x + 1, y, z,          0.0f, 0.0f, -1.0f,
        x + 1, y + 1, z,      0.0f, 0.0f, -1.0f,
        x, y + 1, z,          0.0f, 0.0f, -1.0f,
        // Autres faces...
    };

    // Indices d'un cube
    GLuint cubeIndices[] = {
        0, 1, 2, 2, 3, 0,
        // Autres faces...
    };

    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
    indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));
}