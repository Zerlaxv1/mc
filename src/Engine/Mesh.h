//
// Created by ninod on 18/09/2024.
//

#ifndef MC_MESH_H
#define MC_MESH_H

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
    Mesh();
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
            : vertices(vertices), indices(indices) {}

    void setVariables(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
        this->vertices = vertices;
        this->indices = indices;
    }

    void setupMesh();

    const std::vector<GLfloat>& getVertices() const {
        return vertices;
    }

    const std::vector<GLuint>& getIndices() const {
        return indices;
    }

    static Mesh CombineMeshs(std::vector<Mesh> meshes);

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    friend class Renderer;

    void printVertices();
};


#endif //MC_MESH_H
