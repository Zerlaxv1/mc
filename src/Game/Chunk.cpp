//
// Created by Nino on 11/08/2024.
//

#include "Chunk.h"

#include <iostream>

#include "Block.h"

Chunk::Chunk() {
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                blocks[x][y][z] = Block(Color(100, 20, 150, 100));
            }
        }
    }
}

Chunk::~Chunk() = default;

// Fonction pour activer un voxel
void Chunk::activateBlock(int x, int y, int z) {
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE) {
        blocks[x][y][z].isVisible = true;
    }
}

void Chunk::renderChunk(const Chunk& chunk, GLuint shaderProgram) {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                if (chunk.blocks[x][y][z].isVisible) {
                    Block::generateCubeMesh(vertices, indices, x, y, z);
                }
            }
        }
    }
#if (DEBUG_LEVEL > 0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

    // Create buffers/arrays and bind them

    //VA0 = Vertex Array Object
    //VBO = Vertex Buffer Object
    //EBO = Element Buffer Object
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Use shader program
    glUseProgram(shaderProgram);

    // print indices and vertices
    // std::cout << "Indices: ";
    // for (auto i : indices) {
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;
    //
    // std::cout << "Vertices: ";
    // for (auto v : vertices) {
    //     std::cout << v << ", ";
    // }
    // std::cout << std::endl;

    // Draw cubes
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}