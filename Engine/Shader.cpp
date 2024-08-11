//
// Created by Nino on 10/08/2024.
//

#include <GL/glew.h>
#include "Shader.h"
#include <GL/GL.h>
#include <iostream>
#include <vector>

GLuint Shader::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        std::cerr << "Error creating shader!" << std::endl;
        return 0;
    }

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log.data());
        std::cerr << "Shader compilation error: " << log.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint Shader::createProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint program = glCreateProgram();
    if (program == 0) {
        std::cerr << "Error creating shader program!" << std::endl;
        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, log.data());
        std::cerr << "Shader program linking error: " << log.data() << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// GLuint vertexShader = Shader::compileShader(GL_VERTEX_SHADER, vertexShaderSource);
// GLuint fragmentShader = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
// GLuint shaderProgram = glCreateProgram();
// GLenum error = glGetError();
// if (error != GL_NO_ERROR) {
//     std::cerr << "OpenGL error after glCreateProgram: " << error << std::endl;
//     return -1;
// }
// glAttachShader(shaderProgram, vertexShader);
// glAttachShader(shaderProgram, fragmentShader);
// glLinkProgram(shaderProgram);
// error = glGetError();
// if (error != GL_NO_ERROR) {
//     std::cerr << "OpenGL error after glLinkProgram: " << error << std::endl;
//     return -1;
// }
//
// // Vérifie les erreurs de linkage
// GLint success;
// glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
// if (!success) {
//     auto* infoLog = new GLchar[512];
//     glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//     // Affiche l'erreur
//     std::cerr << "Error linking shader program: " << infoLog << std::endl;
//     delete[] infoLog;
// }
// glDeleteShader(vertexShader);
// glDeleteShader(fragmentShader);