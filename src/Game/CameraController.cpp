//
// Created by ninod on 05/05/2025.
//

#include "CameraController.h"

CameraController::CameraController(Camera* targetCamera, float speed, float sensitivity) {
    camera = targetCamera;
    movementSpeed = speed;
    mouseSensitivity = sensitivity;
    cameraLocked = false;
}

void CameraController::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    camera->ProcessKeyboard(direction, velocity);
}
void CameraController::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    if (cameraLocked) {
        return;
    }

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    camera->ProcessMouseMovement(xoffset, yoffset, constrainPitch);
}
void CameraController::ProcessMouseScroll(float yoffset) {
    camera->ProcessMouseScroll(yoffset);
}
void CameraController::toggleLock() {
    cameraLocked = !cameraLocked;
}