#version 460 core

// Entrées du vertex shader
layout(location = 0) in vec3 aPos;      // Position
layout(location = 1) in vec3 aColor;    // Couleur
layout (location = 2) in vec2 aTexCoord; // Coordonnées de texture

// Sortie vers le fragment shader
out vec3 ourColor;
out vec2 TexCoord;

void main() {
    // Transformation des positions des sommets
    gl_Position = vec4(aPos, 1.0);

    // Passage de la couleur & textures au fragment shader
    ourColor = aColor;
    TexCoord = aTexCoord;
}