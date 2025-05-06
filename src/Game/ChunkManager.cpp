//
// Created by ninod on 06/05/2025.
//

#include "ChunkManager.h"
#include <cmath>
#include <iostream>

Chunk* ChunkManager::getChunk(int x, int y, int z) {
    auto it = chunks.find(std::make_tuple(x, y, z));
    if (it != chunks.end()) return &it->second;
    return nullptr;
}

Chunk& ChunkManager::createChunk(int x, int y, int z) {
    std::cout << "Creating chunk at (" << x << ", " << y << ", " << z << ")" << std::endl;
    auto& chunk = chunks[std::make_tuple(x, y, z)];
    // Initialiser le chunk avec sa position mondiale
    chunk = Chunk(x * chunkSize, z * chunkSize);
    return chunk;
}

void ChunkManager::removeChunk(int x, int y, int z) {
    auto key = std::make_tuple(x, y, z);
    if (chunks.find(key) != chunks.end()) {
        std::cout << "Removing chunk at (" << x << ", " << y << ", " << z << ")" << std::endl;
        chunks.erase(key);
    }
}

bool ChunkManager::chunkExists(int x, int y, int z) const {
    return chunks.find(std::make_tuple(x, y, z)) != chunks.end();
}

void ChunkManager::updateLoadedChunks(const glm::vec3& playerPos) {
    // Convertir la position du joueur en coordonnées de chunk
    auto [playerChunkX, playerChunkY, playerChunkZ] = worldToChunkCoordinates(
        playerPos.x, playerPos.y, playerPos.z, chunkSize);

    // Vérifier tous les chunks qui devraient être chargés et les charger si nécessaire
    for (int x = playerChunkX - renderDistance; x <= playerChunkX + renderDistance; ++x) {
        for (int z = playerChunkZ - renderDistance; z <= playerChunkZ + renderDistance; ++z) {
            // On reste dans le plan Y=0 pour simplifier (jeu 2D en hauteur)
            const int y = 0;
            
            // Si le chunk n'existe pas déjà, le créer
            if (!chunkExists(x, y, z)) {
                Chunk& newChunk = createChunk(x, y, z);
                newChunk.generateFlatChunk(x * chunkSize, z * chunkSize);
            }
        }
    }
    
    // Décharger les chunks trop éloignés
    std::vector<std::tuple<int, int, int>> chunksToRemove;
    
    for (const auto& [pos, _] : chunks) {
        int chunkX = std::get<0>(pos);
        int chunkY = std::get<1>(pos);
        int chunkZ = std::get<2>(pos);
        
        // Si le chunk est trop loin du joueur
        if (std::abs(chunkX - playerChunkX) > renderDistance || 
            std::abs(chunkZ - playerChunkZ) > renderDistance) {
            chunksToRemove.push_back(pos);
        }
    }
    
    // Supprimer les chunks trop éloignés
    for (const auto& pos : chunksToRemove) {
        removeChunk(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos));
    }
}

std::vector<Mesh> ChunkManager::getAllChunkMeshes() {
    std::vector<Mesh> meshes;
    
    std::cout << "Getting meshes from " << chunks.size() << " chunks:" << std::endl;
    
    for (auto& [pos, chunk] : chunks) {
        std::cout << "  - Chunk at (" << std::get<0>(pos) << ", " 
                  << std::get<1>(pos) << ", " << std::get<2>(pos) << ")" << std::endl;
        
        Mesh* chunkMesh = chunk.getChunkMesh();
        if (chunkMesh != nullptr) {
            std::cout << "    Mesh generated with " 
                      << chunkMesh->getVertices().size() / 6 << " vertices" << std::endl;
            meshes.push_back(*chunkMesh);
            delete chunkMesh;
        } else {
            std::cout << "    Failed to generate mesh!" << std::endl;
        }
    }
    
    return meshes;
}

void ChunkManager::generateFlatWorld(int centerX, int centerZ, int sizeX, int sizeZ, int chunkSize) {
    std::cout << "Generating flat world..." << std::endl;
    for (int x = centerX - sizeX; x <= centerX + sizeX; ++x) {
        for (int z = centerZ - sizeZ; z <= centerZ + sizeZ; ++z) {
            Chunk& chunk = createChunk(x, 0, z);
            chunk.generateFlatChunk(x * chunkSize, z * chunkSize);
        }
    }
    std::cout << "Finished generating flat world." << std::endl;
}

std::tuple<int, int, int> ChunkManager::worldToChunkCoordinates(float x, float y, float z, int chunkSize) const {
    // Convertit les coordonnées monde en coordonnées chunk
    int chunkX = static_cast<int>(std::floor(x / chunkSize));
    int chunkY = static_cast<int>(std::floor(y / chunkSize));
    int chunkZ = static_cast<int>(std::floor(z / chunkSize));
    
    return std::make_tuple(chunkX, chunkY, chunkZ);
}