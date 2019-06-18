//
// Created by camix on 28/05/19.
//

#include "Cake.h"
#include <iostream>

Cake::Cake(std::string &path, Window &window, int totalFrames, int id, int w, int h) :
        AnimatedObject(path, window, totalFrames, id, w, h) {}

Cake::~Cake() = default;

std::pair<float, float> Cake::matrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(position, CAKE_WIDTH, CAKE_HEIGHT);
}

std::pair<int, int> Cake::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(pair, CAKE_WIDTH, CAKE_HEIGHT);
}
