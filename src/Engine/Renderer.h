//
// Created by Nino on 01/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "Shader.h"


class Renderer {
public:
    void init();

    Renderer();
    Renderer(float verticesArg[], int size , unsigned int indicesArg[], int size2);
    ~Renderer();

    void draw();
    void copyVerticesData(float vertices[], int size);
    void copyIndicesData(unsigned int indices[], int size);

    float vertices;
    unsigned int indices;
private:
    unsigned int VBO, VAO, EBO;
    Shader shader;
};



#endif //RENDERER_H