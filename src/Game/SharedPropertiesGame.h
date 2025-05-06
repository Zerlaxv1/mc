//
// Created by ninod on 05/05/2025.
//
#pragma once
#include <glm/vec3.hpp>

#ifndef SHAREDPROPERTIESGAME_H
#define SHAREDPROPERTIESGAME_H

struct SharedPropertiesGame {
    float cameraSpeed = 8.0f;
    const static int CHUNK_SIZE = 16;
    const static int CHUNK_HEIGHT = 256;
    int renderDistance = 2;
};

#endif //SHAREDPROPERTIESGAME_H