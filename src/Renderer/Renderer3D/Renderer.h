//
// Created by Nino on 01/09/2024.
//

#pragma once

#include "Renderer/Renderer3D/RenderPipeline/Shader.h"
#include "Renderer/Renderer3D/Camera/Camera.h"
#include "Renderer/Renderer3D/SceneGraph/Mesh.h"
#include "Renderer/SharedPropertiesEngine.h"
#include "Renderer/Renderer3D/RenderPipeline/Texture.h"

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