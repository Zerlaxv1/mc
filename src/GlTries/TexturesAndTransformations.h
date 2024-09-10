//
// Created by Nino on 07/09/2024.
//

#ifndef TEXTURESANDTRANSFORMATIONS_H
#define TEXTURESANDTRANSFORMATIONS_H

#include <memory>

#include "../Engine/Shader.h"


class TexturesAndTransformations {
public:
    TexturesAndTransformations();
    void render();
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    std::unique_ptr<Shader> shader =
        std::make_unique<Shader>("./Resources/Shaders/VertexTextures.glsl",
            "./Resources/Shaders/fragmentTextures.glsl");
};



#endif //TEXTURESANDTRANSFORMATIONS_H
