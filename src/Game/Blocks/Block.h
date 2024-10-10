//
// Created by ninod on 24/09/2024.
//

// src/Game/Blocks/Block.h

#ifndef MC_BLOCK_H
#define MC_BLOCK_H

#include <string>
#include <iostream>
#include <vector>
#include "../../Engine/Mesh.h"

class Block {
public:
    int id;
    std::string name;
    int textureIDs[6];
    bool isSolid;
    Mesh mesh;

    Block(int id,
          const std::string &name,
          const int textureIDs[6],
          bool solid = true);

    virtual void onInteract();
};

#endif //MC_BLOCK_H
