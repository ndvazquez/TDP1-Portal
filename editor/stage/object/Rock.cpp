//
// Created by camix on 22/05/19.
//

#include <string>
#include "Rock.h"
#include "../../../common/Window.h"

Rock::Rock(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

Rock::~Rock() = default;


std::pair<float, float> Rock::centerOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, ROCK_WIDTH, ROCK_HEIGHT);
}
