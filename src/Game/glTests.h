//
// Created by Nino on 22/08/2024.
//

#ifndef GLTESTS_H
#define GLTESTS_H
#include <GL/glew.h>


class glTests {
public:
    glTests();
    void renderTest(GLuint shaderProgram);
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
};



#endif //GLTESTS_H
