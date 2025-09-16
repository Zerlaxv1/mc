//
// Created by ninod on 06/05/2025.
//

#pragma once

#include <map>
#include "Game/World/ChunkManager/Chunk/Chunk.h"
#include "Game/SharedPropertiesGame.h"


class ChunkManager {
private:
    std::map<std::tuple<int, int, int>, Chunk> chunks;
    SharedPropertiesGame& sharedPropsGame;
    int renderDistance = 0;
    int chunkSize = 0;
    std::tuple<int,int,int> oldCameraChunkPos;

    Chunk& createChunk(int x, int y, int z);
    bool chunkExists(int x, int y, int z) const;
public:
    ChunkManager(SharedPropertiesGame& sharedPropsGame) : sharedPropsGame(sharedPropsGame), renderDistance(sharedPropsGame.renderDistance), chunkSize(sharedPropsGame.CHUNK_SIZE) {}

    Chunk* getChunk(int x, int y, int z);
    void removeChunk(int x, int y, int z);
    
    bool updateLoadedChunks(const glm::vec3& playerPos);
    std::vector<Mesh> getAllChunkMeshes();
    void generateFlatWorld(int centerX, int centerZ, int sizeX, int sizeZ, int chunkSize);
    std::tuple<int, int, int> worldToChunkCoordinates(float x, float y, float z, int chunkSize) const;
};