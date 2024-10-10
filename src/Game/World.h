//
// Created by Nino on 11/08/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <tuple>
#include "Chunk.h"
#include "../Engine/Camera.h"
#include "../Engine/Renderer.h"

class World {
public:
    std::map<std::tuple<int, int, int>, Chunk> chunks;

    World();

    // static void renderWorld(const World& world, GLuint shaderProgram);
    Chunk* getChunk(int x, int y, int z);
    void activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ);
    void generateFlatWorld();
    void render();
    void ProcessKeyboard(Camera_Movement movement, float deltatime);
    void ProcessMouseMovement(double xpos, double ypos, bool cond);
    void setAspectRatio(int i, int i1);
    void combineChunkMeshes();
private:
    Renderer renderer;
    Mesh combinedMesh;
    Shader shader;
    Camera camera;
    Texture texture;
};

#endif //WORLD_H