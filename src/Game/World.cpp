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

// return the chunk at the given position
Chunk* World::getChunk(int x, int y, int z) {
    auto it = chunks.find(std::make_tuple(x, y, z));
    if (it != chunks.end()) {
        return &it->second;
    }
    return nullptr; // Chunk non trouvé (hors du monde chargé)
}

// activate the block at the given position in the given chunk
void World::activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
    Chunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    chunk->activateBlock(voxelX, voxelY, voxelZ);
}

// void World::renderWorld(const World& world, GLuint shaderProgram) {
    // for (const auto& [pos, chunk] : world.chunks) {
    //     Chunk::renderChunk(chunk, shaderProgram);
    // }
// }

// call the generateFlatChunk function for each chunk in the world
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

// render world
void World::render() {
    renderer.draw();
}

// process keyboard input
void World::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    renderer.ProcessKeyboard(movement, deltatime);
}

// process mouse input
void World::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    renderer.ProcessMouseMovement(xpos, ypos, cond);
}

// set the window size
void World::setAspectRatio(int i, int i1) {
    renderer.setAspectRatio(i, i1);
}

// combine all the chunk meshes into one mesh (to reduce draw calls)
void World::combineChunkMeshes() {
    std::vector<Mesh> chunkMeshes;

    for (auto& [pos, chunk] : chunks) {
        Mesh* mesh = chunk.getChunkMesh();
        if (mesh != nullptr) {
            chunkMeshes.push_back(*mesh);
        }
    }

    combinedMesh = Mesh::CombineMeshs(chunkMeshes);
}

// constructor
World::World() :
shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
camera(glm::vec3(0.0f, 0.0f, 3.0f)),
renderer(&combinedMesh, &shader, &camera, &texture)
{
    generateFlatWorld();
    combineChunkMeshes();
    renderer.setAspectRatio(800, 600);
    renderer.init();
}