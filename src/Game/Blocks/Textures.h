//
// Created by ninod on 24/09/2024.
//

#ifndef MC_TEXTURES_H
#define MC_TEXTURES_H

#include <unordered_map>
#include <string>

enum TextureID {
    GRASS_TOP = 0,
    GRASS_SIDE = 1,
    DIRT_FACE = 2,
    STONE_FACE = 3,
};

struct TextureStruct {
    TextureID id;
    const char* path;
};

class Textures {
public:
    Textures();
    std::vector<std::string> getTextureVector();
private:
    std::unordered_map<TextureID, TextureStruct> textureList;
};


#endif //MC_TEXTURES_H
