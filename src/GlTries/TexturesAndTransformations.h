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

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    std::unique_ptr<Shader> shader =
        std::make_unique<Shader>("./Resources/Shaders/VertexTextures.glsl",
            "./Resources/Shaders/fragmentTextures.glsl");
};



#endif //TEXTURESANDTRANSFORMATIONS_H
