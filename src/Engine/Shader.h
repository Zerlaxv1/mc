//
// Created by Nino on 10/08/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

class Shader {
public:
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    void createProgram();
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    GLuint shaderProgram;

    GLuint compileShader(GLenum type, const char* source);
};



#endif //SHADER_H
