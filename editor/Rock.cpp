//
// Created by camix on 22/05/19.
//

#include <string>
#include "Rock.h"
#include "../common/Window.h"

Rock::Rock(std::string& path, Window& window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

Rock::~Rock() = default;

void Rock::addTo(int x, int y, std::map<std::pair<int, int>, std::string>& tiles) {
    Object::addWithGravityTo(x, y, tiles);
}
