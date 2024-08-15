//
// Created by Nino on 11/08/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <tuple>
#include "Chunk.h"

class World {
public:
    std::map<std::tuple<int, int, int>, Chunk> chunks;

    Chunk& getChunk(int x, int y, int z);
    void activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ);
    static void renderWorld(const World& world);
};

#endif //WORLD_H