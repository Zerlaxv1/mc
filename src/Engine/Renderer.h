//
// Created by Nino on 01/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

class Renderer {
public:
    Renderer(Mesh* mesh, Shader& shader, Camera& camera, Texture& texture);
    ~Renderer();

    void init();
    void draw();
    void ProcessKeyboard(Camera_Movement movement, float deltaTime);
    void ProcessMouseMovement(double xpos, double ypos, bool cond);

    void setAspectRatio(int i, int i1);

private:
    unsigned int VBO, VAO, EBO;
    Shader shader;
    Mesh* mesh;
    Camera camera;
    Texture texture;
    float AspectRatio;
};



#endif //RENDERER_H
