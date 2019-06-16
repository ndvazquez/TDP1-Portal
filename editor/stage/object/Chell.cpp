//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Chell.h"

Chell::Chell(std::string& path, Window& window, int totalFrames ,const std::string& name, int w, int h) :
        AnimatedObject(path, window, totalFrames, name, w, h) {}

Chell::~Chell() = default;

std::pair<float, float> Chell::centerOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, CHELL_WIDTH, CHELL_HEIGHT);
}
