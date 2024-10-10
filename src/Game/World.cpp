//
// Created by Nino on 11/08/2024.
//

#include "World.h"

//Chunk& World::getChunk(int x, int y, int z) {
//    std::tuple<int, int, int> pos = std::make_tuple(x, y, z);
//    if (chunks.find(pos) == chunks.end()) {
//        chunks[pos] = Chunk();
//    }
//    return chunks[pos];
//}

Chunk* World::getChunk(int x, int y, int z) {
    auto it = chunks.find(std::make_tuple(x, y, z));
    if (it != chunks.end()) {
        return &it->second;
    }
    return nullptr; // Chunk non trouvé (hors du monde chargé)
}

void World::activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
    Chunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    chunk->activateBlock(voxelX, voxelY, voxelZ);
}

// void World::renderWorld(const World& world, GLuint shaderProgram) {
    // for (const auto& [pos, chunk] : world.chunks) {
    //     Chunk::renderChunk(chunk, shaderProgram);
    // }
// }

void World::generateFlatWorld() {
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                Chunk& chunk = chunks[std::make_tuple(x, y, z)];
                chunk.generateFlatChunk(x, y, z);
            }
        }
    }
}

void World::render() {
    renderer.draw();
}

void World::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    renderer.ProcessKeyboard(movement, deltatime);
}

void World::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    renderer.ProcessMouseMovement(xpos, ypos, cond);
}

void World::setAspectRatio(int i, int i1) {
    renderer.setAspectRatio(i, i1);
}

void World::combineChunkMeshes() {
    std::vector<float> combinedVertices;
    std::vector<unsigned int> combinedIndices;
    unsigned int indexOffset = 0;

    for (const auto& [pos, chunk] : chunks) {
        Mesh* chunkMesh = chunk.getChunkMesh();
        const auto& vertices = chunkMesh->getVertices();
        const auto& indices = chunkMesh->getIndices();

        combinedVertices.insert(combinedVertices.end(), vertices.begin(), vertices.end());

        for (unsigned int index : indices) {
            combinedIndices.push_back(index + indexOffset);
        }

        indexOffset += vertices.size() / 6; // Assuming each vertex has 6 attributes (3 for position, 2 for texture, 1 for texture index)
    }

    combinedMesh.setVariables(combinedVertices.data(), combinedIndices.data(), combinedVertices.size(), combinedIndices.size());
}

World::World() :
shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
camera(glm::vec3(0.0f, 0.0f, 3.0f)),
renderer(&combinedMesh, &shader, &camera, &texture)
{
    combineChunkMeshes();
    renderer.setAspectRatio(800, 600);
    renderer.init();
}
