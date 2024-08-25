//
// Created by Nino on 22/08/2024.
//

#include "glTests.h"

#include <iostream>

glTests::glTests() {
    VBO = 0;
    VAO = 0;
    EBO = 0;
    float vertices[] = {
        // positions            // colors
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   // top left
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

    /* GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
     GL_STATIC_DRAW: the data is set only once and used many times.
     GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */


    // positions ( location = 0 ), 3 floats, not normalized, stride = 6 *, offset = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colors ( location = 1 ), 3 floats, not normalized, stride = 6, offset = 3
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void glTests::renderTest(GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
