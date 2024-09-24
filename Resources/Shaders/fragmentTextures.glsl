#version 460 core
in vec3 TexCoords;
out vec4 FragColor;

uniform sampler2DArray TextureArray;

void main() {
    FragColor = texture(TextureArray, TexCoords);
}