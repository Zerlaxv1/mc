//
// Created by ninod on 05/05/2025.
//

#pragma once

#include "Game/SharedPropertiesGame.h"
#include "Renderer/Renderer3D/Camera/Camera.h"

// Dans Game/CameraController.h
class CameraController {
private:
    Camera* camera;
    float& movementSpeed;
    float mouseSensitivity;
    bool cameraLocked;

public:
    CameraController(Camera* targetCamera,SharedPropertiesGame* sharedProperties , float speed = 2.5f, float sensitivity = 0.1f);

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void toggleLock();
};
