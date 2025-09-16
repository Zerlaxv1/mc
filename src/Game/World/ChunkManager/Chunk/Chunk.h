//
// Created by Nino on 11/08/2024.
//

#pragma once

#include "Game/SharedPropertiesGame.h"
#include "Renderer/Renderer3D/SceneGraph/Mesh.h"
#include "Blocks.h"
#include <vector>

class Chunk {
public:
    int CHUNK_SIZE;
    int CHUNK_HEIGHT;
    std::vector<BlockID> blocks;

    Chunk(int worldX = 0, int worldZ = 0);
    ~Chunk();

    void activateBlock(int x, int y, int z);
    void generateFlatChunk(int i, int i2);
    void setBlock(int x, int y, int z, BlockID block);

    BlockID getBlock(int x, int y, int z);
    Mesh *getChunkMesh();

    void addBlockFaces(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, int x, int y, int z,
                       GLuint &indexOffset);

    void addFaceVertices(std::vector<GLfloat> &vertices, const std::vector<GLfloat> &blockVertices, int x, int y, int z,
                         int face);

    void addFaceIndices(std::vector<GLuint> &indices, const std::vector<GLuint> &blockIndices, GLuint indexOffset,
                        int face);

    bool isTransparent(int x, int y, int z) const;
private:
    int chunkWorldX = 0;
    int chunkWorldZ = 0;
};
