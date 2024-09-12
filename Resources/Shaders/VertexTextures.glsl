#version 460 core

// Entrées du vertex shader
layout(location = 0) in vec3 aPos;      // Position
layout (location = 1) in vec2 aTexCoord; // Coordonnées de texture

// Sortie vers le fragment shader
out vec2 TexCoord;

uniform mat4 transform;

void main() {
    // Transformation des positions des sommets
    gl_Position = transform * vec4(aPos, 1.0);

    // Passage de la textures au fragment shader
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}