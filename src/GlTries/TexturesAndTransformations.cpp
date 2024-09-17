//
// Created by Nino on 07/09/2024.
//

#include <GL/glew.h>
#include "TexturesAndTransformations.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

TexturesAndTransformations::TexturesAndTransformations() {
    VBO = 0;
    VAO = 0;
    EBO = 0;

    constexpr float vertices[] = {
            // positions          // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    // Créer un Vertex Buffer Object, il va contenir les vertices (data de sommets)
    glGenBuffers(1, &VBO);
    // Créer un Vertex Array Object, il va contenir les configurations des attributs de sommets
    glGenVertexArrays(1, &VAO);
    // Créer un Element Buffer Object, il va contenir les indices des vertices
    glGenBuffers(1, &EBO);


    ///VAO
    // bind Vertex Array Object
    glBindVertexArray(VAO);

    ///VBO
    // dire à OpenGL que lle VBO est un GL_ARRAY_BUFFER ( contient les sommets )
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // copy vertices data into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ///EBO
    // dire à OpenGL que lle EBO est un GL_ELEMENT_ARRAY_BUFFER ( lie les sommets pour former des triangles )
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*
     GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
     GL_STATIC_DRAW: the data is set only once and used many times.
     GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */


    // positions ( location = 0 ), 3 floats, not normalized, stride = 5 *, offset = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // texture ( location = 1 ), 2 floats, not normalized, stride = 5 *, offset = 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //// Texture

    // init things
    unsigned int texture;
    int width, height, nrChannels;

    // generate 1 texture
    glGenTextures(1, &texture);

    // bind texture to a 2D texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load image
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("./Resources/Textures/dirt.png", &width, &height, &nrChannels, 0);

    if (data) {
        // generate texture from image data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // generate mipmap for the texture
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    // free space
    stbi_image_free(data);

    // debug triangles
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //init camera
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void TexturesAndTransformations::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    shader->use();
    glBindVertexArray(VAO);


    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ///view matrix
    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // projection matrix
    // fov, aspect ratio (16:9, 4:3), near (everything under is not rendered), far (everything above is not rendered)
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader->setMatrix4fv("view", glm::value_ptr(view));
    shader->setMatrix4fv("projection", glm::value_ptr(projection));

    for (unsigned int i = 0; i < 10; i++) {
        //model matrix
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);

        float angle = 25.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        // set the matrices
        shader->setMatrix4fv("model", glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void TexturesAndTransformations::cameraMovement(Camera_Movement c) {
    const float cameraSpeed = 5.0f * deltaTime;
    if (c == FORWARD) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (c == BACKWARD) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (c == LEFT) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (c == RIGHT) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (c == UP) {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (c == DOWN) {
        cameraPos -= cameraSpeed * cameraUp;
    }
}
void TexturesAndTransformations::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}