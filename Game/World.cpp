//
// Created by Nino on 11/08/2024.
//

#include "World.h"

Chunk& World::getChunk(int x, int y, int z) {
    std::tuple<int, int, int> pos = std::make_tuple(x, y, z);
    if (chunks.find(pos) == chunks.end()) {
        chunks[pos] = Chunk();
    }
    return chunks[pos];
}


void World::activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
    Chunk& chunk = getChunk(chunkX, chunkY, chunkZ);
    chunk.activateBlock(voxelX, voxelY, voxelZ);
}

void World::renderWorld(const World& world) {
    for (const auto& [pos, chunk] : world.chunks) {
        Chunk::renderChunk(chunk);
    }
}