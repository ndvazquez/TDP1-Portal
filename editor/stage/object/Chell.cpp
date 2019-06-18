//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Chell.h"

Chell::Chell(std::string &path, Window &window, int totalFrames, int id, int w, int h) :
        AnimatedObject(path, window, totalFrames, id, w, h) {}

Chell::~Chell() = default;

std::pair<float, float> Chell::MatrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, CHELL_WIDTH, CHELL_HEIGHT);
}
