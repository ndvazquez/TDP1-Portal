//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

void Block::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles) {
    auto positionAbove = tiles.find(std::make_pair(x, y - 1));
    // if i have something above me and is not another block
    if (positionAbove != tiles.end() && positionAbove->second != name) {
            // I can't be removed
            throw RemoveTileFloorNeeded(this->name);
    }
    Object::removeFrom(x, y, tiles);
}

Block::~Block() = default;
