//
// Created by Nino on 10/08/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <GL/gl.h>

class Shader {
public:
    static GLuint compileShader(GLenum type, const char* source);

    static GLuint createProgram(const char *vertexSource, const char *fragmentSource);
};



#endif //SHADER_H
