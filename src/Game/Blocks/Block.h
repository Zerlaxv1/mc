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
    // Block ID
    int id;
    // Block name
    std::string name;
    // Texture IDs
    // 0: front, 1: back, 2: left, 3: right, 4: bottom, 5: top
    int textureIDs[6];
    // Is the block solid?
    bool isSolid;
    // Is the block transparent?
    bool Transparency;
    Mesh mesh;

    Block(
        int id,
        const std::string &name,
        const int textureIDs[6],
        bool solid = true,
        bool transparency = false
    );

    // when the block is interacted with (right-click)
    virtual void onInteract();
    // does the black have transparency?
    bool isTransparent() const;
};

#endif //MC_BLOCK_H
