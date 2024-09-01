//
// Created by Nino on 10/08/2024.
//

#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include "Shader.h"
#include <GL/GL.h>
#include <iostream>
#include <vector>

std::string readShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint Shader::compileShader(GLenum type, const char* source) {
    // Create shader of specified type
    GLuint shader = glCreateShader(type);

    if (shader == 0) {
        std::cerr << "Error creating shader!" << std::endl;
        return 0;
    }

    // specify the shader source code
    glShaderSource(shader, 1, &source, nullptr);

    // compile the shader
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // Get the length of the error log
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log.data());

        std::cerr << "Shader compilation error: " << log.data() << std::endl;
        glDeleteShader(shader);
        return -1;
    }

    return shader;
}

void Shader::createProgram() {
    // Compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    // Create shader program
    shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        std::cerr << "Error creating shader program!" << std::endl;
        return;
    }

    // Attach shaders and link program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(shaderProgram, logLength, &logLength, log.data());
        std::cerr << "Shader program linking error: " << log.data() << std::endl;
        glDeleteProgram(shaderProgram);
        return;
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader() {
    shaderProgram = 0;
    vertexShaderSource = readShaderSource("./Resources/Shaders/Vertex.glsl");
    fragmentShaderSource = readShaderSource("./Resources/Shaders/fragment.glsl");
    createProgram();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    shaderProgram = 0;
    vertexShaderSource = readShaderSource(vertexPath);
    fragmentShaderSource = readShaderSource(fragmentPath);
    createProgram();
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}