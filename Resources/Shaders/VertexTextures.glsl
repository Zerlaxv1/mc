#version 460 core

// Entrées du vertex shader
layout(location = 0) in vec3 inPos;               // Position
layout (location = 1) in vec2 inTexCoords;  // Coordonnées de texture
layout(location = 2) in float inTexLayer;         // Layer de la texture

// Sortie vers le fragment shader
out vec3 TexCoords;

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Transformation des positions des sommets
    gl_Position = projection * view * model * vec4(inPos, 1.0);

    // Passage de la textures au fragment shader
    TexCoords = vec3(inTexCoords, inTexLayer);
}