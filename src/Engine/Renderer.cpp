//
// Created by Nino on 01/09/2024.
//
#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void GLAPIENTRY MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
    std::cerr << "GL CALLBACK: " << ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ) <<
              " type = 0x" << std::hex << type << ", severity = 0x" << severity << ", message = " << message << std::endl;
}

void Renderer::init() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    VBO = 0;
    VAO = 0;
    EBO = 0;

    // Créer un Vertex Buffer Object, il va contenir les vertices (data de sommets)
    glGenBuffers(1, &VBO);
    // Créer un Vertex Array Object, il va contenir les configurations des attributs de sommets
    glGenVertexArrays(1, &VAO);
    // Créer un Element Buffer Object, il va contenir les indices des vertices
    glGenBuffers(1, &EBO);

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error, generation Buffers :" << err << std::endl;
    }

    ///VAO
    // bind Vertex Array Object
    glBindVertexArray(VAO);

    ///VBO
    // dire à OpenGL que lle VBO est un GL_ARRAY_BUFFER ( contient les sommets )
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    ///EBO
    // dire à OpenGL que lle EBO est un GL_ELEMENT_ARRAY_BUFFER ( lie les sommets pour former des triangles )
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //test for error
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error, Binding Buffers :" << err << std::endl;
    }

    // setup mesh
    // glBufferData for vertices and indices
    mesh.setupMesh();

    //test for error
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    // positions ( location = 0 ), 3 floats, not normalized, stride = 5 *, offset = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // texture ( location = 1 ), 2 floats, not normalized, stride = 5 *, offset = 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //test for error
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    setAspectRatio(800, 600);

    //debug
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    glBindVertexArray(0); // Unbind VAO après configuration
}

Renderer::Renderer(Mesh& mesh, Shader& shader, Camera& camera, Texture& texture ) : mesh(mesh), shader(shader), camera(camera), texture(texture) {
    init();
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    glBindVertexArray(VAO);

    //model matrix
    glm::mat4 model = glm::mat4(1.0f);

    ///view matrix
    glm::mat4 view = camera.GetViewMatrix();

    //debug
//    std::cout << "View Matrix: \n" << glm::to_string(view) << std::endl;

    // projection matrix
    // fov, aspect ratio (16:9, 4:3), near (everything under is not rendered), far (everything above is not rendered)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), AspectRatio, 0.1f, 100.0f);

    //debug
//    std::cout << "Projection Matrix: \n" << glm::to_string(projection) << std::endl;

//    // Lire les données du VBO
//    std::vector<float> bufferData(mesh.verticesSize);
//    glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferData.size() * sizeof(float), bufferData.data());
//
//// Afficher les données
//    for (float value : bufferData) {
//        std::cout << value << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "Indices size: " << mesh.verticesSize << std::endl;
//
//    // Lire les données de l'EBO
//    std::vector<GLuint> indices(mesh.indicesSize);
//    glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
//
//// Afficher les données
//    for (GLuint index : indices) {
//        std::cout << index << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "Indices size: " << mesh.indicesSize << std::endl;

    shader.setMatrix4fv("model", glm::value_ptr(model));
    shader.setMatrix4fv("view", glm::value_ptr(view));
    shader.setMatrix4fv("projection", glm::value_ptr(projection));

    if (mesh.indicesSize > 0) {
        glDrawElements(GL_TRIANGLES, mesh.indicesCount, GL_UNSIGNED_INT, 0);
    } else {
        std::cerr << "Error: mesh.indicesSize is zero or negative!" << std::endl;
    }

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
    glBindVertexArray(0);
}

void Renderer::ProcessKeyboard(Camera_Movement movement, float deltatime) {
    camera.ProcessKeyboard(movement, deltatime);
}

void Renderer::ProcessMouseMovement(double xpos, double ypos, bool cond) {
    camera.ProcessMouseMovement(xpos, ypos, cond);
}

void Renderer::setAspectRatio(int width, int height) {
    AspectRatio = static_cast<float>(width) / static_cast<float>(height);
}
