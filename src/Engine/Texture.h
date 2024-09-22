//
// Created by ninod on 18/09/2024.
//

#ifndef OPENGL_TESTS_TEXTURE_H
#define OPENGL_TESTS_TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <bits/stl_vector.h>

class Texture {
public:

    explicit Texture(const char* imagePath);
    void bind();

private:
    GLuint textureID;
    unsigned char *loadTexture(const char *path, int *width, int *height, int *nrChannels);
    void createTexture(const char* imagePath);
    GLuint createTextureArray(const std::vector<std::string> &texturePaths);
};


#endif //OPENGL_TESTS_TEXTURE_H
