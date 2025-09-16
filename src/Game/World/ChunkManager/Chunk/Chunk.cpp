//
// Created by Nino on 11/08/2024.
//

#include "Chunk.h"
#include <array>
#include "Game/World/ChunkManager/Chunk/Blocks.h"

// generate a chunk with all blocks set to air
Chunk::Chunk(int worldX, int worldZ) : chunkWorldX(worldX), chunkWorldZ(worldZ),
                                       blocks(CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE, BlockID::AIR),
                                       CHUNK_SIZE(SharedPropertiesGame::CHUNK_SIZE),
                                       CHUNK_HEIGHT(SharedPropertiesGame::CHUNK_HEIGHT) {}

// Destructor
Chunk::~Chunk()
{
    // Rien à faire, std::vector gère la mémoire
}

// Helper pour convertir (x, y, z) en index 1D
inline int getBlockIndex(int x, int y, int z)
{
    return x + SharedPropertiesGame::CHUNK_SIZE * (y + SharedPropertiesGame::CHUNK_HEIGHT * z);
}

// Fonction pour activer un voxel
void Chunk::activateBlock(int x, int y, int z)
{
    // TODO: Implement
}

// return the block at the given position
BlockID Chunk::getBlock(int x, int y, int z)
{
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE)
        return BlockID::AIR;
    return blocks[getBlockIndex(x, y, z)];
}

// set the block at the given position
void Chunk::setBlock(int x, int y, int z, BlockID block)
{
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_SIZE)
    {
        blocks[getBlockIndex(x, y, z)] = block;
    }
}

// generate a chunk with Grass and Stone in the center in cross on the x and z axis
void Chunk::generateFlatChunk(int worldX, int worldZ)
{
    // Générer une couche de base en pierre
    for (int x = 0; x < CHUNK_SIZE; ++x)
    {
        for (int z = 0; z < CHUNK_SIZE; ++z)
        {
            // Couche de pierre de Y=0 à Y=3
            for (int y = 0; y <= 3; ++y)
            {
                blocks[getBlockIndex(x, y, z)] = BlockID::STONE;
            }

            // Couche de terre de Y=4 à Y=6
            for (int y = 4; y <= 6; ++y)
            {
                blocks[getBlockIndex(x, y, z)] = BlockID::DIRT;
            }

            // Couche d'herbe à Y=7
            blocks[getBlockIndex(x, 7, z)] = BlockID::GRASS;
        }
    }
}

/**
 * Generates the mesh for the chunk.
 *
 * @return A pointer to the generated Mesh object.
 */
Mesh *Chunk::getChunkMesh()
{
    // mesh = vector de vertices et indices
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint indexOffset = 0;

    vertices.reserve(CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 4 * 6);
    indices.reserve(CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 6);

    // Parcourir chaque bloc dans le chunk et ajouter ses faces au mesh
    for (int x = 0; x < CHUNK_SIZE; ++x)
    {
        for (int y = 0; y < CHUNK_HEIGHT; ++y)
        {
            for (int z = 0; z < CHUNK_SIZE; ++z)
            {
                if (!isTransparent(x, y, z))
                {
                    addBlockFaces(vertices, indices, x, y, z, indexOffset);
                }
            }
        }
    }

    // Mode débogage: ajouter une boîte englobante au chunk en fil de fer
    bool addWireframe = true;
    if (addWireframe)
    {
        // Couleur rouge pour la wireframe (en utilisant la texture 0)
        float wireframeTextureID = 0.0f;

        // Position dans l'espace du chunk
        // Dans getChunkMesh(), modifiez les positions du wireframe:
        float minX = chunkWorldX;
        float minY = 0.0f; // Y=0 pour le fil de fer
        float minZ = chunkWorldZ;
        float maxX = static_cast<float>(CHUNK_SIZE) + chunkWorldX;
        float maxY = static_cast<float>(CHUNK_HEIGHT) + minY;
        float maxZ = static_cast<float>(CHUNK_SIZE) + chunkWorldZ;

        // 8 sommets d'un cube
        std::vector<std::array<float, 3>> cubeVertices = {
            {minX, minY , minZ}, {maxX, minY, minZ}, {maxX, maxY, maxZ}, {minX, maxY, maxZ}, {minX, minY, minZ}, {maxX, maxY, maxZ}, {maxX, maxY, maxZ}, {minX, maxY, maxZ}};

        // 12 arêtes du cube (indices des sommets)
        std::vector<std::array<int, 2>> cubeEdges = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Face inférieure
            {4, 5},
            {5, 6},
            {6, 7},
            {7, 4}, // Face supérieure
            {0, 4},
            {1, 5},
            {2, 6},
            {3, 7} // Arêtes verticales
        };

        // Ajouter des lignes pour le wireframe
        for (const auto &edge : cubeEdges)
        {
            // Premier sommet de l'arête
            vertices.push_back(cubeVertices[edge[0]][0]);
            vertices.push_back(cubeVertices[edge[0]][1]);
            vertices.push_back(cubeVertices[edge[0]][2]);
            vertices.push_back(0.0f); // U
            vertices.push_back(0.0f); // V
            vertices.push_back(wireframeTextureID);

            // Deuxième sommet de l'arête
            vertices.push_back(cubeVertices[edge[1]][0]);
            vertices.push_back(cubeVertices[edge[1]][1]);
            vertices.push_back(cubeVertices[edge[1]][2]);
            vertices.push_back(1.0f); // U
            vertices.push_back(1.0f); // V
            vertices.push_back(wireframeTextureID);

            // Indices pour les lignes
            indices.push_back(indexOffset);
            indices.push_back(indexOffset + 1);

            indexOffset += 2;
        }
    }

    return new Mesh(std::move(vertices), std::move(indices));
}

/**
 * Adds the faces of a block to the mesh.
 *
 * @param vertices The vector of vertices to add to.
 * @param indices The vector of indices to add to.
 * @param x The x-coordinate of the block.
 * @param y The y-coordinate of the block.
 * @param z The z-coordinate of the block.
 * @param indexOffset The current index offset.
 */
void Chunk::addBlockFaces(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, int x, int y, int z,
                          GLuint &indexOffset)
{
    const Block &block = Blocks::getBlock(blocks[getBlockIndex(x, y, z)]);
    const auto &blockVertices = block.mesh.getVertices();
    const auto &blockIndices = block.mesh.getIndices();

    // Debug: afficher l'ID du bloc et ses indices de texture
    // std::cout << "Bloc en (" << x << "," << y << "," << z << ") ID: " << blocks[x][y][z] << std::endl;
    // for (int i = 0; i < 6; i++) {
    //     std::cout << "  Face " << i << " texture: " << block.textureIDs[i] << std::endl;
    // }

    // Définir les directions des faces
    constexpr std::array<std::tuple<int, int, int>, 6> faceDirections = {
        std::make_tuple(0, 0, -1), // Front (Z-)
        std::make_tuple(0, 0, 1),  // Back (Z+)
        std::make_tuple(-1, 0, 0), // Left (X-)
        std::make_tuple(1, 0, 0),  // Right (X+)
        std::make_tuple(0, -1, 0), // Bottom (Y-)
        std::make_tuple(0, 1, 0)   // Top (Y+)
    };

    // Pour chaque face du bloc
    for (int face = 0; face < 6; ++face)
    {
        const auto &[dx, dy, dz] = faceDirections[face];
        const int adjX = x + dx;
        const int adjY = y + dy;
        const int adjZ = z + dz;

        // Ne rendre la face que si le bloc adjacent est transparent
        if (isTransparent(adjX, adjY, adjZ))
        {
            // Chaque face a 4 sommets, chaque sommet a 6 valeurs
            const size_t faceVertexStart = face * 4 * 6;

            // Ajouter les 4 sommets de la face
            for (int i = 0; i < 4; ++i)
            {
                const size_t vOffset = faceVertexStart + i * 6;

                // Position du sommet (déplacée à la position du bloc)
                vertices.push_back(blockVertices[vOffset] + x + chunkWorldX);     // X
                vertices.push_back(blockVertices[vOffset + 1] + y);               // Y
                vertices.push_back(blockVertices[vOffset + 2] + z + chunkWorldZ); // Z

                // Coordonnées de texture (inchangées)
                vertices.push_back(blockVertices[vOffset + 3]); // U
                vertices.push_back(blockVertices[vOffset + 4]); // V

                // ID de texture
                vertices.push_back(blockVertices[vOffset + 5]); // TextureID
            }

            // Ajouter les 6 indices pour former 2 triangles
            const size_t faceIndexStart = face * 6;
            for (int i = 0; i < 6; ++i)
            {
                // Ajouter l'indice en tenant compte du décalage
                indices.push_back(blockIndices[faceIndexStart + i] - (face * 4) + indexOffset);
            }

            // Incrémenter le décalage d'indices pour le prochain bloc
            indexOffset += 4;
        }
    }
}

/**
 * Adds the vertices of a face to the mesh.
 *
 * @param vertices The vector of vertices to add to.
 * @param blockVertices The vertices of the block.
 * @param x The x-coordinate of the block.
 * @param y The y-coordinate of the block.
 * @param z The z-coordinate of the block.
 * @param face The face index.
 */
void Chunk::addFaceVertices(std::vector<GLfloat> &vertices, const std::vector<GLfloat> &blockVertices, int x, int y,
                            int z, int face)
{
    // Chaque face a 4 vertices, chaque vertex a 6 floats
    const size_t vertexOffset = face * 4 * 6;

    // Déboguer les coordonnées de la face
    // TODO: face 2 et 3 sont presque jamais rendu
    std::cout << "Face " << face << " at (" << x << ", " << y << ", " << z << ")" << std::endl;

    // for (size_t i = 0; i < 4; ++i) {
    //     const size_t offset = vertexOffset + i * 6;
    //     vertices.push_back(blockVertices[offset] + x);
    //     vertices.push_back(blockVertices[offset + 1] + y);
    //     vertices.push_back(blockVertices[offset + 2] + z);
    //     vertices.push_back(blockVertices[offset + 3]);
    //     vertices.push_back(blockVertices[offset + 4]);
    //     vertices.push_back(blockVertices[offset + 5]);
    // }

    for (size_t i = 0; i < 4; ++i)
    {
        const size_t offset = vertexOffset + i * 6;
        if (offset + 5 < blockVertices.size())
        {
            // Vérification de dépassement
            vertices.push_back(blockVertices[offset] + x);
            vertices.push_back(blockVertices[offset + 1] + y);
            vertices.push_back(blockVertices[offset + 2] + z);
            vertices.push_back(blockVertices[offset + 3]); // Coordonnée U de texture
            vertices.push_back(blockVertices[offset + 4]); // Coordonnée V de texture
            vertices.push_back(blockVertices[offset + 5]); // ID de texture
        }
    }
}

/**
 * Adds the indices of a face to the mesh.
 *
 * @param indices The vector of indices to add to.
 * @param blockIndices The indices of the block.
 * @param indexOffset The current index offset.
 * @param face The face index.
 */
void Chunk::addFaceIndices(std::vector<GLuint> &indices, const std::vector<GLuint> &blockIndices, GLuint indexOffset,
                           int face)
{
    // Chaque face a 6 indices (2 triangles)
    const size_t indexOffsetPerFace = face * 6;

    // for (size_t i = 0; i < 6; ++i) {
    //     indices.push_back(blockIndices[indexOffsetPerFace + i] + indexOffset);
    // }
    if (indexOffsetPerFace + 5 < blockIndices.size())
    {
        // Vérification de dépassement
        for (size_t i = 0; i < 6; ++i)
        {
            // Supprimez le modulo 24
            indices.push_back(blockIndices[indexOffsetPerFace + i] + indexOffset);
        }
    }
}

// Nouvelle méthode helper dans Chunk.h
bool Chunk::isTransparent(int x, int y, int z) const
{
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE)
        return true;
    return Blocks::getBlock(blocks[getBlockIndex(x, y, z)]).isTransparent();
}
