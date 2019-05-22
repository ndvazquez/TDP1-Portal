//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window, const std::string& name) :
    StaticObject(path, window), name(name) {}

bool Block::canBeOn(const std::string &name) {
    return !(name == "Chell");
}

bool Block::canBeOn() {
    return true;
}

bool Block::canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string>& names) {
    auto below = names.find(std::make_pair(x, y + 1));
    if (below != names.end()) {
        std::cerr << "uno abajo tengo: " << below->second << std::endl;
    }
    return !(below != names.end() && (below->second == "Chell" || below->second == "Gate"));
}


Block::~Block() = default;
