//
// Created by ninod on 18/09/2024.
//

#ifndef OPENGL_TESTS_MESH_H
#define OPENGL_TESTS_MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    void draw();

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VAO, VBO, EBO;
    void setupMesh();
};


#endif //OPENGL_TESTS_MESH_H
