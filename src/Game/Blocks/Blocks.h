//
// Created by ninod on 24/09/2024.
//

#ifndef MC_BLOCKS_H
#define MC_BLOCKS_H

#include "Block.h"

enum BlockID {
    DIRT = 1,
    GRASS = 2,
    STONE = 3,
};

class Blocks {
public:
    static void initialize();
    static Block getBlock(BlockID id);
    static const std::vector<Block>& getBlockList();
private:
    static std::vector<Block> blockList;
};


#endif //MC_BLOCKS_H
