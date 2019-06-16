//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

bool Block::hasGravity() {
    return false;
}

void Block::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                       std::unordered_map<std::string, Object *>& textures) {
    auto positionAbove = tiles.find(std::make_pair(x, y - 1));

    /// if(name == BLOCK_SENTINEL) return;


    // if i have something above me
    if (positionAbove != tiles.end()){
        std::string& tileName = positionAbove->second;
        Object* objAbove = textures[tileName];
        // and is has gravity
        if (objAbove->hasGravity()) {
            // I can't be removed
            throw RemoveTileFloorNeeded(this->name);
        }
    }
    Object::removeFrom(x, y, tiles, textures);
}

Block::~Block() = default;
