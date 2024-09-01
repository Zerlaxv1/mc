//
// Created by Nino on 22/08/2024.
//

#ifndef GLTESTS_H
#define GLTESTS_H

#include "../Engine/Shader.h"

class glTests {
public:
    glTests();
    void renderTest();
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    Shader shader;
    // unsigned int shaderprgrm;
};



#endif //GLTESTS_H
