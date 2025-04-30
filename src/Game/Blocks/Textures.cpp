//
// Created by ninod on 24/09/2024.
//

#include <vector>
#include "Textures.h"
#include <iostream>

#include "../../Engine/Texture.h"

std::map<TextureID, const char*> Textures::textureList;

Textures::Textures() {
    if (textureList.empty()) {
        std::cout << "Initializing textures" << std::endl;
        initializeTextures();
        std::cout << "textureList initialized with " << textureList.size() << " textures." << std::endl;
    } else {
        std::cout << "Textures already initialized." << std::endl;
    }
}

//transform textureList to a vector of strings
std::vector<std::string> Textures::getTextureVector() {
    std::vector<std::string> texturePaths;
    for (auto &i: textureList) {
        texturePaths.push_back(i.second);
    }
    return texturePaths;
}

void Textures::initializeTextures() {
    textureList[GRASS_TOP] = "./Resources/Textures/grass-top.png";
    textureList[GRASS_SIDE] =  "./Resources/Textures/grass-side.png";
    textureList[DIRT_FACE] = "./Resources/Textures/dirt.png";
    textureList[STONE_FACE] = "./Resources/Textures/stone.png";
}
