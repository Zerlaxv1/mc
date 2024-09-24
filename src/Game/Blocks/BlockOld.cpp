//
// Created by Nino on 11/08/2024.
//

#include "BlockOld.h"
#include <vector>
#include <GL/glew.h>

BlockOld::BlockOld() {
}

void BlockOld::generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float x, float y, float z) {
    // Front face
    vertices.insert(vertices.end(), {
            x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f,  // 0
            x + 0.5f, y - 0.5f, z - 0.5f, 1.0f, 0.0f,  // 1
            x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f,  // 2
            x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 1.0f,  // 3
    });
    indices.insert(indices.end(), {
            0, 1, 2,
            2, 3, 0,
    });

    // Back face
    vertices.insert(vertices.end(), {
            x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f,  // 4
            x + 0.5f, y - 0.5f, z + 0.5f, 1.0f, 0.0f,  // 5
            x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f,  // 6
            x - 0.5f, y + 0.5f, z + 0.5f, 0.0f, 1.0f,  // 7
    });
    indices.insert(indices.end(), {
            4, 5, 6,
            6, 7, 4,
    });
}