//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftUp.h"

DiagonalBlockLeftUp::DiagonalBlockLeftUp(std::string &path, Window &window,
                                         int id, int w, int h) :
        DiagonalBlockUp(path, window, id, w, h) {}

DiagonalBlockLeftUp::~DiagonalBlockLeftUp() = default;

std::pair<float, float> DiagonalBlockLeftUp::matrixPosToCenterOfMass(
        const std::pair<int, int> &pair) {
    float x = pair.first;
    float y = pair.second;

    float x1 = x + (2.0/3) * w;
    float y1 = y - (1.0/3) * h;
    return std::pair<float, float> (x1, y1 + 1);
}

std::pair<int, int> DiagonalBlockLeftUp::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;

    int x1 = std::round(x - (2.0/3) * w);
    float y1 = std::round(y + (1.0/3) * h);
    return std::pair<int, int> (x1, y1 - 1);
}
