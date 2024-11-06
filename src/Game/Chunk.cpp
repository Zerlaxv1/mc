//
// Created by Nino on 11/08/2024.
//

#include "Chunk.h"
#include "Blocks/BlockOld.h"
#include "Blocks/Blocks.h"

// generate a chunk with all blocks set to air
Chunk::Chunk() {
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_DEPTH; ++z) {
                blocks[x][y][z] = BlockID::AIR; // Air ou bloc vide
            }
        }
    }
}

// Destructor
Chunk::~Chunk() {

}

// Fonction pour activer un voxel
void Chunk::activateBlock(int x, int y, int z) {
    //TODO: Implement
}

// return the block at the given position
BlockID Chunk::getBlock(int x, int y, int z) {
    if (x < 0 || x >= Chunk::CHUNK_WIDTH || y < 0 || y >= Chunk::CHUNK_HEIGHT || z < 0 || z >= Chunk::CHUNK_DEPTH)
        return BlockID::AIR; // Hors du chunk
    return blocks[x][y][z];
}

// set the block at the given position
void Chunk::setBlock(int x, int y, int z, BlockID block) {
    if (x >= 0 && x < Chunk::CHUNK_WIDTH && y >= 0 && y < Chunk::CHUNK_HEIGHT && z >= 0 && z < Chunk::CHUNK_DEPTH) {
        blocks[x][y][z] = block;
    }
}

//generate a chunk with Grass and Stone in the center in cross on the x and z axis
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
    std::cout << "Generating mesh for chunk" << std::endl;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint indexOffset = 0;

    for (int x = 0; x < Chunk::CHUNK_WIDTH; ++x) {
        for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < Chunk::CHUNK_DEPTH; ++z) {
                if (blocks[x][y][z] != BlockID::AIR) {
                    const Block& block = Blocks::getBlock(blocks[x][y][z]);
                    const std::vector<GLfloat>& blockVertices = block.mesh.getVertices();
                    const std::vector<GLuint>& blockIndices = block.mesh.getIndices();

                    // Add vertices for the block
                    for (size_t i = 0; i < blockVertices.size(); i += 6) {
                        vertices.push_back(blockVertices[i] + x);
                        vertices.push_back(blockVertices[i + 1] + y);
                        vertices.push_back(blockVertices[i + 2] + z);
                        vertices.push_back(blockVertices[i + 3]);
                        vertices.push_back(blockVertices[i + 4]);
                        vertices.push_back(blockVertices[i + 5]);
                    }

                    // Add indices for the block
                    for (GLuint index : blockIndices) {
                        indices.push_back(index + indexOffset);
                    }

                    indexOffset += static_cast<GLuint>(blockVertices.size() / 6);
                }
            }
        }
    }

    return new Mesh(vertices, indices);
}