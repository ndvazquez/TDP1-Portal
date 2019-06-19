//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockRightDown.h"

DiagonalBlockRightDown::DiagonalBlockRightDown(std::string &path, Window &window,
                                               int id, int w, int h) :
        DiagonalBlockDown(path, window, id, w, h) {}

DiagonalBlockRightDown::~DiagonalBlockRightDown() = default;

std::pair<float, float> DiagonalBlockRightDown::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    float x = position.first;
    float y = position.second;

    float x1 = x + (1.0/3) * w;
    float y1 = y - (2.0/3) * h;
    return std::pair<float, float> (x1, y1 + 1);
}

std::pair<int, int> DiagonalBlockRightDown::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;

    float x1 = std::round(x - (1.0/3) * w);
    float y1 = std::round(y + (2.0/3) * h);
    return std::pair<int, int> (x1, y1 - 1);
}
