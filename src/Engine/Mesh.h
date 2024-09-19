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

inline std::vector<Vertex> arrayToVertexVector(const float* array, size_t size) {
    std::vector<Vertex> vertices;
    for (size_t i = 0; i < size; i += 5) {
        Vertex vertex;
        vertex.Position = glm::vec3(array[i], array[i + 1], array[i + 2]);
        vertex.TexCoords = glm::vec2(array[i + 3], array[i + 4]);
        vertices.push_back(vertex);
    }
    return vertices;
}

inline std::vector<GLuint> arrayToGLuintVector(const GLuint* array, size_t size) {
    return std::vector<GLuint>(array, array + size);
}

class Mesh {
public:
    Mesh(float *vertices, unsigned int *indices, unsigned int verticesCount, unsigned int indicesCount);
    void setupMesh();

private:
    float *vertices;
    unsigned int *indices;
    unsigned int verticesSize;
    unsigned int indicesSize;
    unsigned int verticesCount;
    unsigned int indicesCount;
    friend class Renderer;

    void printVertices();
};


#endif //OPENGL_TESTS_MESH_H
