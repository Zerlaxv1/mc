//
// Created by Nino on 11/08/2024.
//

#ifndef CHUNK_H
#define CHUNK_H
#include "Block.h"


class Chunk {
public:
    static const int CHUNK_SIZE = 16;
    Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    Chunk();
    ~Chunk();
    void activateBlock(int x, int y, int z);
    static void renderChunk(const Chunk& chunk, GLuint shaderProgram);
};



#endif //CHUNK_H
