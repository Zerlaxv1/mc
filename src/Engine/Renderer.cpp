//
// Created by Nino on 01/09/2024.
//

#include "Renderer.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

void Renderer::init() {
    VBO, VAO, EBO = 0;

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

    ///EBO
    // dire à OpenGL que lle EBO est un GL_ELEMENT_ARRAY_BUFFER ( lie les sommets pour former des triangles )
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // positions ( location = 0 ), 3 floats, not normalized, stride = 5 *, offset = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // texture ( location = 1 ), 2 floats, not normalized, stride = 5 *, offset = 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // setup mesh
    // glBufferData for vertices and indices
    mesh.setupMesh();

    //debug
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::Renderer(Mesh& mesh, Shader& shader, Camera& camera, Texture& texture ) : mesh(mesh), shader(shader), camera(camera), texture(texture) {
    init();
}

Renderer::~Renderer() = default;

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    shader.use();
    glBindVertexArray(VAO);

    ///view matrix
    glm::mat4 view = camera.GetViewMatrix();

    // projection matrix
    // fov, aspect ratio (16:9, 4:3), near (everything under is not rendered), far (everything above is not rendered)
    // TODO: make the aspect ratio dynamic
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);

    // Ensure the size does not exceed the maximum value of GLsizei
    // si ca marche pas c'est a cause de cette magie noire
    GLsizei indexCount = static_cast<GLsizei>(std::min(mesh.indices.size(), static_cast<size_t>(std::numeric_limits<GLsizei>::max())));

    shader.setMatrix4fv("view", glm::value_ptr(view));
    shader.setMatrix4fv("projection", glm::value_ptr(projection));
    shader.setMatrix4fv("model", glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Renderer::setTexture(const char *texturePath) : texture(texturePath) {
    texture.bind();
}

void Renderer::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    camera.ProcessKeyboard(movement, deltatime);
}

void Renderer::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    camera.ProcessMouseMovement(xpos, ypos, cond);
}
