//
// Created by ninod on 18/09/2024.
//

#include "Texture.h"
#include <iostream>
#include <vector>

#include "../tools/stb_image.h"

// Chargement d'une texture depuis un fichier
unsigned char* Texture::loadTexture(const char* path, int* width, int* height, int* nrChannels = 0) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, width, height, nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture at: " << path << std::endl;
        return nullptr;
    }
    return data;
}

Texture::Texture(const char* imagePath) {
    //inutile vu qu'on a qu'une seule texture mais bon
    glActiveTexture(GL_TEXTURE0);
    createTexture(imagePath);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::createTexture(const char* imagePath) {
    glGenTextures(1, &textureID);
    bind();

    //test for error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //test for error
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    int width, height, nrChannels;
    unsigned char* data = loadTexture(imagePath, &width, &height, &nrChannels);

    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        //test for error
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error while creating mipmap : " << err << std::endl;
        }
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

// Créer une texture 2D array et charger toutes les textures dans des fichiers séparés
GLuint Texture::createTextureArray(const std::vector<std::string>& texturePaths) {
    int width, height;
    std::vector<unsigned char*> textureData;

    // Charger toutes les textures dans la mémoire
    for (const std::string& path : texturePaths) {
        unsigned char* data = loadTexture(path.c_str(), &width, &height);
        if (data != nullptr) {
            textureData.push_back(data);
        } else {
            std::cerr << "Failed to load texture at: " << path << std::endl;
        }
    }

    // Créer la texture array 2D dans OpenGL
    GLuint textureArray;
    glGenTextures(1, &textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

    // Créer la texture avec toutes les couches
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, textureData.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Charger chaque texture dans une couche de la texture array
    for (size_t i = 0; i < textureData.size(); ++i) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, textureData[i]);
        stbi_image_free(textureData[i]);  // Libérer la mémoire une fois chargée
    }

    // Configurer les paramètres de filtrage et de wrapping
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Pas de lissage, pour un style pixelisé
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureArray;
}
