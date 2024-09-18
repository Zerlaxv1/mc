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

std::vector<Vertex> arrayToVertexVector(const float* array, size_t size) {
    std::vector<Vertex> vertices;
    for (size_t i = 0; i < size; i += 5) {
        Vertex vertex;
        vertex.Position = glm::vec3(array[i], array[i + 1], array[i + 2]);
        vertex.TexCoords = glm::vec2(array[i + 3], array[i + 4]);
        vertices.push_back(vertex);
    }
    return vertices;
}

std::vector<GLuint> arrayToGLuintVector(const GLuint* array, size_t size) {
    return std::vector<GLuint>(array, array + size);
}

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void setupMesh();

    friend class Renderer;
};


#endif //OPENGL_TESTS_MESH_H
