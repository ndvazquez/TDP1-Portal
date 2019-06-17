//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockUp.h"

DiagonalBlockUp::DiagonalBlockUp(std::string &path, Window &window,
                            const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool DiagonalBlockUp::hasGravity() {
    return false;
}

void DiagonalBlockUp::addTo(int x, int y, std::map<std::pair<int, int>,
                     std::string> &tiles, std::unordered_map<std::string,
                     Object *> &texturesL, bool needGravitySentinel) {
    Object::addTo(x, y, tiles, texturesL, true);
}

DiagonalBlockUp::~DiagonalBlockUp() = default;