//
// Created by ninod on 18/09/2024.
//

#ifndef OPENGL_TESTS_TEXTURE_H
#define OPENGL_TESTS_TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
public:
    explicit Texture();

    void bind();
    GLuint createTextureArray(const std::vector<std::string> &texturePaths);
private:
    GLuint textureArray;
    unsigned char *loadTexture(const char *path, int *width, int *height, int *nrChannels);
    void createTexture(const char* imagePath);
};


#endif //OPENGL_TESTS_TEXTURE_H
