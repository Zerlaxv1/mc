//
// Created by Nino on 11/08/2024.
//

#include "World.h"

#include "Game/World/ChunkManager/Chunk/Textures.h"

// return the chunk at the given position
Chunk *World::getChunk(int x, int y, int z) {
    return chunkManager.getChunk(x, y, z);
}

// void World::updateLoadedChunks() {
//     chunkManager.updateLoadedChunks(sharedPropsEngine.cameraPos);
//     // Re-combiner les meshes après avoir mis à jour les chunks
//     combineChunkMeshes();
// }

// activate the block at the given position in the given chunk
void World::activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
    Chunk *chunk = getChunk(chunkX, chunkY, chunkZ);
    if (chunk != nullptr) {
        chunk->activateBlock(voxelX, voxelY, voxelZ);
    } else {
        std::cerr << "Chunk not found at (" << chunkX << ", " << chunkY << ", " << chunkZ << ")" << std::endl;
    }
}

// render world
void World::render() {
    if (chunkManager.updateLoadedChunks(sharedPropsEngine.cameraPos)) {
        combineChunkMeshes();
    }

    renderer.draw();
}

// process keyboard input
void World::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    cameraController.ProcessKeyboard(movement, deltatime);
}

// process mouse input
void World::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    cameraController.ProcessMouseMovement(xpos, ypos, cond);
}

// set the window size
void World::setAspectRatio(int i, int i1) {
    renderer.setAspectRatio(i, i1);
}

// combine all the chunk meshes into one mesh (to reduce draw calls)
void World::combineChunkMeshes() {
    std::vector<Mesh> chunkMeshes = chunkManager.getAllChunkMeshes();

    if (!chunkMeshes.empty()) {
        std::cout << "Combined " << chunkMeshes.size() << " chunk meshes" << std::endl;
        combinedMesh = Mesh::CombineMeshes(chunkMeshes);
    } else {
        std::cout << "No chunk meshes found" << std::endl;
    }
}

void World::toggleCameraLock() {
    cameraController.toggleLock();
}

// constructor
World::World() : renderer(&combinedMesh, &shader, &camera, &texture, &sharedPropsEngine),
                 camera(Camera(&sharedPropsEngine)),
                 shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
                 cameraController(&camera, &sharedPropsGame),
                 chunkManager(sharedPropsGame) {
}

void World::Init() {
    // Textures
    Textures texturesManager;
    std::vector<std::string> texturePaths = texturesManager.getTextureVector();
    texture.createTextureArray(texturePaths);

    // Map
    chunkManager.generateFlatWorld(0, 0, sharedPropsGame.renderDistance, sharedPropsGame.renderDistance,
                                   sharedPropsGame.CHUNK_SIZE);
    // generateFlatWorld();
    combineChunkMeshes();

    // Init
    renderer.setAspectRatio(800, 600);
    renderer.init();
}
