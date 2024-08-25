//
// Created by Nino on 11/08/2024.
//

#include "Block.h"
#include <vector>
#include <GL/glew.h>

Block::Block(Color color) : color(color) {
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

        x, y, z + 1,          0.0f, 0.0f, 1.0f,
        x + 1, y, z + 1,      0.0f, 0.0f, 1.0f,
        x + 1, y + 1, z + 1,  0.0f, 0.0f, 1.0f,
        x, y + 1, z + 1,      0.0f, 0.0f, 1.0f,

        x, y, z,              -1.0f, 0.0f, 0.0f,
        x, y, z + 1,          -1.0f, 0.0f, 0.0f,
        x, y + 1, z + 1,      -1.0f, 0.0f, 0.0f,
        x, y + 1, z,          -1.0f, 0.0f, 0.0f,

        x + 1, y, z,          1.0f, 0.0f, 0.0f,
        x + 1, y, z + 1,      1.0f, 0.0f, 0.0f,
        x + 1, y + 1, z + 1,  1.0f, 0.0f, 0.0f,
        x + 1, y + 1, z,      1.0f, 0.0f, 0.0f,

        x, y, z,              0.0f, -1.0f, 0.0f,
        x + 1, y, z,          0.0f, -1.0f, 0.0f,
        x + 1, y, z + 1,      0.0f, -1.0f, 0.0f,
        x, y, z + 1,          0.0f, -1.0f, 0.0f,

        x, y + 1, z,          0.0f, 1.0f, 0.0f,
        x + 1, y + 1, z,      0.0f, 1.0f, 0.0f,
        x + 1, y + 1, z + 1,  0.0f, 1.0f, 0.0f,
        x, y + 1, z + 1,      0.0f, 1.0f, 0.0f
    };

    // Indices d'un cube
    GLuint cubeIndices[] = {
        0, 1, 2, 2, 3, 0,       // Face avant
        4, 5, 6, 6, 7, 4,       // Face arrière
        8, 9, 10, 10, 11, 8,    // Face gauche
        12, 13, 14, 14, 15, 12, // Face droite
        16, 17, 18, 18, 19, 16, // Face bas
        20, 21, 22, 22, 23, 20  // Face haut
    };

    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
    indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));
}