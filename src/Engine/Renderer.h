//
// Created by Nino on 01/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "SharedPropertiesEngine.h"
#include "Texture.h"

class Renderer {
public:
    Renderer(Mesh* mesh, Shader* shader, Camera* camera, Texture* texture, SharedPropertiesEngine* sharedProps);
    ~Renderer();

    void init();
    void draw();

    void setAspectRatio(int i, int i1);

private:
    unsigned int VBO, VAO, EBO;
    Shader* shader;
    Mesh* mesh;
    Camera* camera;
    Texture* texture;
    SharedPropertiesEngine* sharedPropsEngine;
    float AspectRatio;
};



#endif //RENDERER_H
