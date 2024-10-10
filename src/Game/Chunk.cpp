//
// Created by Nino on 11/08/2024.
//

#include "Chunk.h"
#include "Blocks/BlockOld.h"
#include "Blocks/Blocks.h"

Chunk::Chunk() {
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_DEPTH; ++z) {
                blocks[x][y][z] = BlockID::AIR; // Air ou bloc vide
            }
        }
    }
}

Chunk::~Chunk() {

}

// Fonction pour activer un voxel
void Chunk::activateBlock(int x, int y, int z) {
    //TODO: Implement
}

BlockID Chunk::getBlock(int x, int y, int z) {
    if (x < 0 || x >= Chunk::CHUNK_WIDTH || y < 0 || y >= Chunk::CHUNK_HEIGHT || z < 0 || z >= Chunk::CHUNK_DEPTH)
        return BlockID::AIR; // Hors du chunk
    return blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, BlockID block) {
    if (x >= 0 && x < Chunk::CHUNK_WIDTH && y >= 0 && y < Chunk::CHUNK_HEIGHT && z >= 0 && z < Chunk::CHUNK_DEPTH) {
        blocks[x][y][z] = block;
    }
}

//not a flat chunk but a cross in x and z
void Chunk::generateFlatChunk(int i, int i1, int i2) {
    int centerX = CHUNK_WIDTH / 2;
    int centerY = CHUNK_HEIGHT / 2;
    int centerZ = CHUNK_DEPTH / 2;

    // Create a line along the x-axis at the center
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        blocks[x][centerY][centerZ] = BlockID::GRASS;
    }

    // Create a line along the z-axis at the center
    for (int z = 0; z < CHUNK_DEPTH; ++z) {
        blocks[centerX][centerY][z] = BlockID::STONE;
    }
}

Mesh *Chunk::getChunkMesh() {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (int x = 0; x < Chunk::CHUNK_WIDTH; ++x) {
        for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < Chunk::CHUNK_DEPTH; ++z) {
                if (blocks[x][y][z] != BlockID::AIR) {
                    vertices.push_back(
                        //blocks[x][y][z]mesh.getVertices()[0]
                        Blocks::getBlock(blocks[x][y][z]).mesh.getVertices()[0] + x);
                        );
                }
            }
        }
    }

    return new Mesh(vertices, indices, vertices.size(), indices.size());
}

// TODO: Delete ?
//void Chunk::renderChunk(const Chunk& chunk, GLuint shaderProgram) {
//    std::vector<GLfloat> vertices;
//    std::vector<GLuint> indices;
//
//    for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
//        for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
//            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
//                // if (chunk.blocks[x][y][z].isVisible) {
//                //     BlockOld::generateCubeMesh(vertices, indices, x, y, z);
//                // }
//            }
//        }
//    }
//#if (DEBUG_LEVEL > 0)
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#endif
//
//    // Create buffers/arrays and bind them
//
//    //VA0 = Vertex Array Object
//    //VBO = Vertex Buffer Object
//    //EBO = Element Buffer Object
//    GLuint VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
//
//    // Define vertex attributes
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    // Use shader program
//    glUseProgram(shaderProgram);
//
//    // print indices and vertices
//    // std::cout << "Indices: ";
//    // for (auto i : indices) {
//    //     std::cout << i << ", ";
//    // }
//    // std::cout << std::endl;
//    //
//    // std::cout << "Vertices: ";
//    // for (auto v : vertices) {
//    //     std::cout << v << ", ";
//    // }
//    // std::cout << std::endl;
//
//    // Draw cubes
//    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//
//    // Cleanup
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteVertexArrays(1, &VAO);
//}