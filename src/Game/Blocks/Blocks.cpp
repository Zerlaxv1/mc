//
// Created by ninod on 24/09/2024.
//

#include "Blocks.h"
#include "Block.h"
#include "Textures.h"

std::vector<Block> Blocks::blockList;

void Blocks::initialize() {
    if (blockList.empty()) {
        std::cout << "Initializing blocks" << std::endl;
        int TextureList0[] = {GRASS_TOP, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, DIRT_FACE};
        blockList.push_back(Block(AIR, "Air", TextureList0));
        int TextureList1[] = {GRASS_TOP, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, DIRT_FACE};
        blockList.push_back(Block(GRASS, "Grass", TextureList1));
        int TextureList2[] = {DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE};
        blockList.push_back(Block(DIRT, "Dirt", TextureList2));
        int TextureList3[] = {STONE, STONE, STONE, STONE, STONE, STONE};
        blockList.push_back(Block(STONE, "Stone", TextureList3));
        std::cout << "blockList initialized with " << blockList.size() << " blocks." << std::endl;
    } else {
        std::cout << "blockList already initialized." << std::endl;
    }
}

const std::vector<Block>& Blocks::getBlockList() {
    return blockList;
}

Block Blocks::getBlock(BlockID id) {
    if (id < blockList.size()) {
        return blockList[id];
    }
    std::cerr << "Invalid BlockID: " << id << std::endl;
    int TextureList3[] = {STONE, STONE, STONE, STONE, STONE, STONE};
    return Block(AIR, "Air", TextureList3); // Retourne un bloc par défaut en cas d'ID invalide
}
