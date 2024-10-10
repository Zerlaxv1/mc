//
// Created by ninod on 24/09/2024.
//

#include "Blocks.h"
#include "Block.h"
#include "Textures.h"


std::vector<Block> Blocks::blockList;

void Blocks::initialize() {
    if (blockList.empty()) {
        int TextureList[] = {GRASS_TOP, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, DIRT_FACE};
        blockList.push_back(Block(GRASS, "Grass", TextureList));
        int TextureList2[] = {DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE};
        blockList.push_back(Block(DIRT, "Dirt", TextureList2));
        int TextureList3[] = {STONE, STONE, STONE, STONE, STONE, STONE};
        blockList.push_back(Block(STONE, "Stone", TextureList3));
    }
}

const std::vector<Block>& Blocks::getBlockList() {
    return blockList;
}

Block Blocks::getBlock(BlockID id) {
    return blockList[id];
}
