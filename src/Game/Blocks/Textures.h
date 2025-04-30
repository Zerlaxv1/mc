//
// Created by ninod on 24/09/2024.
//

#ifndef MC_TEXTURES_H
#define MC_TEXTURES_H

#include <map>
#include <string>

enum TextureID {
    GRASS_TOP = 0,
    GRASS_SIDE = 1,
    DIRT_FACE = 2,
    STONE_FACE = 3,
};

class Textures {
public:
    Textures();
    std::vector<std::string> getTextureVector();
private:
    static std::map<TextureID, const char*> textureList;

    static void initializeTextures();
};


#endif //MC_TEXTURES_H
