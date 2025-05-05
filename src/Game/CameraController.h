//
// Created by ninod on 05/05/2025.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "../Engine/Camera.h"

// Dans Game/CameraController.h
class CameraController {
private:
    Camera* camera;
    float movementSpeed;
    float mouseSensitivity;
    bool cameraLocked;

public:
    CameraController(Camera* targetCamera, float speed = 2.5f, float sensitivity = 0.1f);

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void toggleLock();
};



#endif //CAMERACONTROLLER_H
