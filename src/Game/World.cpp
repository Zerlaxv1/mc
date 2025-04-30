//
// Created by Nino on 11/08/2024.
//

#include "World.h"

#include "Blocks/Textures.h"

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
    if (chunk != nullptr) {
        chunk->activateBlock(voxelX, voxelY, voxelZ);
    } else {
        std::cerr << "Chunk not found at (" << chunkX << ", " << chunkY << ", " << chunkZ << ")" << std::endl;
    }
}


// call the generateFlatChunk function for each chunk in the world
void World::generateFlatWorld() {
    std::cout << "Generating flat world..." << std::endl;
    for (int x = 0; x <= 0; x++) {
        for (int y = 0; y <= 0; y++) {
            for (int z = 0; z <= 0; z++) {
                std::cout << "Generating chunk at (" << x << ", " << y << ", " << z << ")" << std::endl;
                Chunk &chunk = chunks[std::make_tuple(x, y, z)];
                chunk.generateFlatChunk(x, y, z);
            }
        }
    }
    std::cout << "Finished generating flat world." << std::endl;
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
            std::cout << "Adding mesh of chunk (" << std::get<0>(pos) << ", " << std::get<1>(pos) << ", " << std::get<2>(pos) << ")" << std::endl;
            chunkMeshes.push_back(*mesh);
        } else {
            std::cout << "No mesh found for chunk (" << std::get<0>(pos) << ", " << std::get<1>(pos) << ", " << std::get<2>(pos) << ")" << std::endl;
        }
    }
    std::cout << "Combined " << chunkMeshes.size() << " chunk meshes" << std::endl;
    combinedMesh = Mesh::CombineMeshes(chunkMeshes);
    // print vertices and indices
    // for (int i = 0; i < 6000; i += 6) {
    //     std::cout << "Vertex " << i / 6 << " : X = " << combinedMesh.getVertices()[i] << ", Y = " << combinedMesh.getVertices()[i + 1] << ", Z = " << combinedMesh.getVertices()[i + 2] << std::endl;
    // }
    // print the number of vertices and indices in the combined mesh
    // std::cout << "Combined mesh has " << combinedMesh.getVertices().size() / 6 << " vertices and " << combinedMesh.getIndices().size() << " indices" << std::endl;

    // print coos of all chunk created
    // for (auto &[pos, chunk]: chunks) {
    //     std::cout << "Chunk at " << std::get<0>(pos) << " " << std::get<1>(pos) << " " << std::get<2>(pos) << std::endl;
    // }
}

void World::toggleCameraLock() {
    camera.toggleLock();
}

// constructor
World::World() : renderer(&combinedMesh, &shader, &camera, &texture, &sharedProps),
                 shader("./Resources/Shaders/VertexTextures.glsl", "./Resources/Shaders/fragmentTextures.glsl"),
                 camera(glm::vec3(0.0f, 3.0f, 0.0f)) {
}

void World::Init() {

    // Créer une instance de Textures
    Textures texturesManager;

    // Obtenir les chemins des textures
    std::vector<std::string> texturePaths = texturesManager.getTextureVector();

    // Charger les textures dans le tableau de textures
    texture.createTextureArray(texturePaths);

    generateFlatWorld();
    combineChunkMeshes();
    renderer.setAspectRatio(800, 600);
    renderer.init();
}
