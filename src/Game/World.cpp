//
// Created by Nino on 11/08/2024.
//

#include "World.h"

// return the chunk at the given position
Chunk *World::getChunk(int x, int y, int z) {
    auto it = chunks.find(std::make_tuple(x, y, z));
    if (it != chunks.end()) {
        return &it->second;
    }
    return nullptr; // Chunk non trouvé (hors du monde chargé)
}

// activate the block at the given position in the given chunk
void World::activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
    Chunk *chunk = getChunk(chunkX, chunkY, chunkZ);
    chunk->activateBlock(voxelX, voxelY, voxelZ);
}


// call the generateFlatChunk function for each chunk in the world
void World::generateFlatWorld() {
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                Chunk &chunk = chunks[std::make_tuple(x, y, z)];
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
    // array of all the meshes
    std::vector<Mesh> chunkMeshes;

    for (auto &[pos, chunk]: chunks) {
        Mesh *mesh = chunk.getChunkMesh();

        std::cout << "Mesh of chunk (" << std::get<0>(pos) << ", " << std::get<1>(pos) << ", " << std::get<2>(pos) <<
                ")"
                << " has " << mesh->getVertices().size() / 6
                << " vertices and "
                << mesh->getIndices().size()
                << " indices" << std::endl;

        if (mesh != nullptr) {
            chunkMeshes.push_back(*mesh);
        }
    }
    std::cout << "Combined " << chunkMeshes.size() << " chunk meshes" << std::endl;
    combinedMesh = Mesh::CombineMeshes(chunkMeshes);
    // print vertices and indices
    for (int i = 0; i < 200; i += 6) {
        std::cout << "Vertex " << i / 6 << " : X = " << combinedMesh.getVertices()[i] << ", Y = " << combinedMesh.
                getVertices()[i + 1] << ", Z = " << combinedMesh.getVertices()[i + 2] << std::endl;
    }
    // print the number of vertices and indices in the combined mesh
    std::cout << "Combined mesh has " << combinedMesh.getVertices().size() / 6 << " vertices and " << combinedMesh.
            getIndices().size() << " indices" << std::endl;

    // print coos of all chunk created
    for (auto &[pos, chunk]: chunks) {
        std::cout << "Chunk at " << std::get<0>(pos) << " " << std::get<1>(pos) << " " << std::get<2>(pos) << std::endl;
    }
}

void World::toggleCameraLock() {
    camera.toggleLock();
}

// constructor
World::World() : renderer(&combinedMesh, &shader, &camera, &texture),
                 shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
                 camera(glm::vec3(0.0f, 128.0f, 0.0f)) {
}

void World::Init() {
    generateFlatWorld();
    combineChunkMeshes();
    renderer.setAspectRatio(800, 600);
    renderer.init();
}
