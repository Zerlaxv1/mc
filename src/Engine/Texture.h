//
// Created by ninod on 18/09/2024.
//

#ifndef OPENGL_TESTS_TEXTURE_H
#define OPENGL_TESTS_TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
    explicit Texture(const char* imagePath);
    void bind();

private:
    GLuint textureID;
    void loadTexture(const char* imagePath);
};


#endif //OPENGL_TESTS_TEXTURE_H
