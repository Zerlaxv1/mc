//
// Created by Nino on 07/09/2024.
//

#ifndef TEXTURESANDTRANSFORMATIONS_H
#define TEXTURESANDTRANSFORMATIONS_H

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "../Engine/Shader.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class TexturesAndTransformations {
public:
    TexturesAndTransformations();
    void render();
    void cameraMovement(Camera_Movement c);

    void processInput(GLFWwindow *window);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;

    glm::vec3 cubePositions[10] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    std::unique_ptr<Shader> shader =
        std::make_unique<Shader>("./Resources/Shaders/VertexTextures.glsl",
            "./Resources/Shaders/fragmentTextures.glsl");

};



#endif //TEXTURESANDTRANSFORMATIONS_H
