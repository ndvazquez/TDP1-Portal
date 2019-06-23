//
// Created by camix on 11/06/19.
//

#include "DiagonalBlockRightUp.h"

DiagonalBlockRightUp::DiagonalBlockRightUp(std::string &path, Window &window,
                                           int id, int w, int h) :
        DiagonalBlockUp(path, window, id, w, h) {}

DiagonalBlockRightUp::~DiagonalBlockRightUp() = default;

std::pair<float, float> DiagonalBlockRightUp::matrixPosToCenterOfMass(
        const std::pair<int, int> &pair) {
    float x = pair.first;
    float y = pair.second;

    float x1 = x + (1.0/3) * w;
    float y1 = y - (1.0/3) * h;
    return std::pair<float, float> (x1, y1 + 1);
}

std::pair<int, int> DiagonalBlockRightUp::centerOfMassToMatrixPos(
        const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;

    float x1 = std::round(x - (1.0/3) * w);
    float y1 = std::round(y + (1.0/3) * h);
    return std::pair<int, int> (x1, y1 - 1);
}
