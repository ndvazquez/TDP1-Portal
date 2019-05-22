//
// Created by camix on 22/05/19.
//

#include <string>
#include "Rock.h"
#include "../common/Window.h"

Rock::Rock(std::string &path, Window &window) : StaticObject(path, window) {}

bool Rock::canBeOn() {
    return false;
}

Rock::~Rock() = default;

bool Rock::canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string> &names) {
    auto it = names.find(std::make_pair(x, y + 1));
    if (it == names.end()) {
        return false;
    }
    return Object::canBeOn(it->second);
}
