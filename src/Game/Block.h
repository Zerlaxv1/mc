//
// Created by Nino on 11/08/2024.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <GL/glew.h>
#include "../tools/Color.h"

class Block {
public:
    explicit Block();
    static void generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float x, float y, float z);
};



#endif //BLOCK_H
