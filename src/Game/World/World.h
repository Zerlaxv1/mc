//
// Created by Nino on 11/08/2024.
//

#pragma once

#include <map>
#include <tuple>

#include "Game/GameSystems/CameraController.h"
#include "Game/World/ChunkManager/Chunk/Chunk.h"
#include "Renderer/Renderer3D/Camera/Camera.h"
#include "Renderer/Renderer3D/Renderer.h"
#include "Game/SharedPropertiesGame.h"
#include "Game/World/ChunkManager/ChunkManager.h"

class World {
public:
    // map, id is a tuple of 3 integers (x, y, z), value is a Chunk
    std::map<std::tuple<int, int, int>, Chunk> chunks;

    World();

    void Init();

    Chunk* getChunk(int x, int y, int z);
    void activateBlock(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ);
    // void updateLoadedChunks();
    void combineChunkMeshes();

    // void generateFlatWorld();
    void render();
    void ProcessKeyboard(Camera_Movement movement, float deltatime);
    void ProcessMouseMovement(double xpos, double ypos, bool cond);
    void setAspectRatio(int i, int i1);
    void toggleCameraLock();

    SharedPropertiesEngine sharedPropsEngine;
    SharedPropertiesGame sharedPropsGame;
private:
    Renderer renderer;
    Mesh combinedMesh;
    Shader shader;
    Camera camera;
    Texture texture;

    CameraController cameraController;
    ChunkManager chunkManager;
};