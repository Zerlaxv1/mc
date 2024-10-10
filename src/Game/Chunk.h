//
// Created by Nino on 11/08/2024.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "Blocks/Block.h"
#include "../Engine/Mesh.h"
#include "Blocks/Blocks.h"

class Chunk {
public:
    static const int CHUNK_WIDTH = 16;
    static const int CHUNK_HEIGHT = 256;
    static const int CHUNK_DEPTH = 16;
    BlockID blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];

    Chunk();
    ~Chunk();

    void activateBlock(int x, int y, int z);
    void generateFlatChunk(int i, int i1, int i2);
    void setBlock(int x, int y, int z, BlockID block);

    BlockID getBlock(int x, int y, int z);
    Mesh *getChunkMesh();
};



#endif //CHUNK_H
