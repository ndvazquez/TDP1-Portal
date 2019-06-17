//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockUp.h"

DiagonalBlockUp::DiagonalBlockUp(std::string &path, Window &window,
                                 int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool DiagonalBlockUp::hasGravity() {
    return false;
}

void DiagonalBlockUp::addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                            std::unordered_map<int, Object *> &texturesL, bool needGravitySentinel) {
    Object::addTo(x, y, tiles, texturesL, true);
}

DiagonalBlockUp::~DiagonalBlockUp() = default;