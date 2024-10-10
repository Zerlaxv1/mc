//
// Created by ninod on 24/09/2024.
//

#include <vector>
#include "Textures.h"
#include "../../Engine/Texture.h"

Textures::Textures() {
    textureList[GRASS_TOP] = {GRASS_TOP, "grass_top.png"};
    textureList[GRASS_SIDE] = {GRASS_SIDE, "grass_side.png"};
    textureList[DIRT_FACE] = {DIRT_FACE, "dirt.png"};
    textureList[STONE_FACE] = {STONE_FACE, "stone.png"};
}

//transform textureList to a vector of strings
std::vector<std::string> Textures::getTextureVector() {
    std::vector<std::string> texturePaths;
    for (auto &i: textureList) {
        texturePaths.push_back(i.second.path);
    }
    return texturePaths;
}
