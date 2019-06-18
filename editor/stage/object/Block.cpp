//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

bool Block::hasGravity() {
    return false;
}


/*   If i want this feature i should added to WithoutGravitySentinel
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
*/
std::pair<float, float> Block::centerOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, METAL_SIDE, METAL_SIDE);
}

Block::~Block() = default;
