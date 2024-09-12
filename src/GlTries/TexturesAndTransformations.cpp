//
// Created by Nino on 07/09/2024.
//

#include "TexturesAndTransformations.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

TexturesAndTransformations::TexturesAndTransformations() {
    VBO = 0;
    VAO = 0;
    EBO = 0;
    float vertices[] = {
        // positions                                                // texture
        0.5f,  0.5f, 0.0f,          1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,          1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture ( location = 1 ), 2 floats, not normalized, stride = 5 *, offset = 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
    unsigned char *data = stbi_load("./Resources/Textures/bg.jpg", &width, &height, &nrChannels, 0);

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

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TexturesAndTransformations::render() {
    shader->use();
    glBindVertexArray(VAO);

    // transformation
    // model matrix
    auto trans = glm::mat4(1.0f);
    // matrix, angle, axis
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.5, 1.0));
    // matrix, scale
    trans = glm::scale(trans, glm::vec3(1.0, 1.5, 0.5));

    shader->setMatrix4fv("transform", glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
