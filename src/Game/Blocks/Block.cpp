//
// Created by ninod on 24/09/2024.
//

#include "Block.h"
#include <algorithm>

Block::Block(int id, const std::string &name, const int *textureIDs, bool solid) : id(id), name(name), isSolid(solid) {
    std::vector<float> vertices = {
            // positions         // texture coords       // texture ID
            // Front face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, (float) textureIDs[0],  // 0
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, (float) textureIDs[0],  // 1
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, (float) textureIDs[0],  // 2
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, (float) textureIDs[0],  // 3

            // Back face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, (float) textureIDs[1],  // 4
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, (float) textureIDs[1],  // 5
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, (float) textureIDs[1],  // 6
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, (float) textureIDs[1],  // 7

            // Left face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, (float) textureIDs[2],  // 8
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, (float) textureIDs[2],  // 9
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, (float) textureIDs[2],  // 10
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, (float) textureIDs[2],  // 11

            // Right face
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, (float) textureIDs[3],   // 12
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, (float) textureIDs[3],   // 13
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, (float) textureIDs[3],   // 14
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, (float) textureIDs[3],   // 15

            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, (float) textureIDs[4],  // 16
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, (float) textureIDs[4],  // 17
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, (float) textureIDs[4],  // 18
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, (float) textureIDs[4],  // 19

            // Top face
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, (float) textureIDs[5],  // 20
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, (float) textureIDs[5],  // 21
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, (float) textureIDs[5],  // 22
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, (float) textureIDs[5]   // 23
    };

    std::vector<unsigned int> indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            8, 9, 10,
            10, 11, 8,

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
    mesh.setVariables(vertices.data(), indices.data(), vertices.size(), indices.size());
    std::copy(textureIDs, textureIDs + 6, this->textureIDs);
}

void Block::onInteract() {
    std::cout << "Interacting with " << name << std::endl;
}