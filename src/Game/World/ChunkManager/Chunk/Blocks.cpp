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

        auto addBlock = [](BlockID id, const std::string& name, const std::vector<int>& textures, bool isSolid, bool isTransparent) {
            blockList.push_back(Block(id, name, textures.data(), isSolid, isTransparent));
        };

        // front, back, left, right, bottom, top
        addBlock(AIR, "Air", {0, 0, 0, 0, 0, 0}, false, true);
        addBlock(DIRT, "Dirt", {DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE, DIRT_FACE}, true, false);
        addBlock(GRASS, "Grass", {GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, DIRT_FACE, GRASS_TOP}, true, false);
        addBlock(STONE, "Stone", {STONE_FACE, STONE_FACE, STONE_FACE, STONE_FACE, STONE_FACE, STONE_FACE}, true, false);

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
