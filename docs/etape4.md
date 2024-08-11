### Plan for Step 4: Rendu de Base

1. **Initialisation de GLEW**:
    - Inclure les en-têtes GLEW.
    - Initialiser GLEW après avoir créé le contexte OpenGL.

2. **Shaders**:
    - Créer des shaders de base (vertex shader et fragment shader).
    - Compiler et lier les shaders à un programme shader.

3. **Rendu de primitives**:
    - Utiliser les shaders pour rendre des triangles.

### Code Implementation

#### 1. Initialisation de GLEW

```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Initialiser GLEW après avoir créé le contexte OpenGL
if (glewInit() != GLEW_OK) {
    // Gérer l'erreur
    return -1;
}
```

#### 2. Shaders

##### Vertex Shader

```cpp
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";
```

##### Fragment Shader

```cpp
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";
```

##### Compilation et Liaison des Shaders

```cpp
// Fonction pour compiler un shader
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    // Vérifier les erreurs de compilation
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        // Gérer l'erreur
    }
    return shader;
}

// Créer et lier le programme shader
GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
// Vérifier les erreurs de linkage
GLint success;
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    // Gérer l'erreur
}
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

#### 3. Rendu de Primitives

##### Initialisation des Données de Vertex

```cpp
float vertices[] = {
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

GLuint VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
```

##### Boucle de Rendu

```cpp
while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Utiliser le programme shader
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteProgram(shaderProgram);
```

Assurez-vous d'avoir initialisé GLFW et créé une fenêtre avant d'exécuter ce code.