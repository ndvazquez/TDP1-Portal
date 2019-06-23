//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftDown.h"

DiagonalBlockLeftDown::DiagonalBlockLeftDown(std::string &path, Window &window,
                                             int id, int w, int h) :
        DiagonalBlockDown(path, window, id, w, h) {}

DiagonalBlockLeftDown::~DiagonalBlockLeftDown() = default;

std::pair<float, float> DiagonalBlockLeftDown::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    float x = position.first;
    float y = position.second;
    float x1 = x + (2.0/3) * w;
    float y1 = y - (2.0/3) * h;
    return std::pair<float, float> (x1, y1 + 1);
}

std::pair<int, int> DiagonalBlockLeftDown::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;

    int x1 = std::round(x - (2.0/3) * w);
    float y1 = std::round(y + (2.0/3) * h);
    return std::pair<int, int> (x1, y1 - 1);
}
