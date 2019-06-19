//
// Created by camix on 22/05/19.
//

#include <string>
#include "Rock.h"
#include "../../../common/Window.h"

Rock::Rock(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

Rock::~Rock() = default;


std::pair<float, float> Rock::matrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(position, ROCK_WIDTH, ROCK_HEIGHT);
}

std::pair<int, int> Rock::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(pair, ROCK_WIDTH, ROCK_HEIGHT);
}
