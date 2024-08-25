#version 460 core

// Entrées du vertex shader
layout(location = 0) in vec3 aPos;      // Position
layout(location = 1) in vec3 aColor;    // Couleur

// Sortie vers le fragment shader
out vec3 ourColor;

void main() {
    // Transformation des positions des sommets
    gl_Position = vec4(aPos, 1.0);

    // Passage de la couleur au fragment shader
    ourColor = aColor;
}