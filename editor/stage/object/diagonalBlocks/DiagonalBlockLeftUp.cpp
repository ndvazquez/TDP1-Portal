//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftUp.h"

DiagonalBlockLeftUp::DiagonalBlockLeftUp(std::string &path, Window &window,
                                         int id, int w, int h) :
        DiagonalBlockUp(path, window, id, w, h) {}

std::pair<int, int> DiagonalBlockLeftUp::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;
    return std::pair<int, int> (x - (1.0/3)  * w, y - (2.0/3) * h + 1);
}

DiagonalBlockLeftUp::~DiagonalBlockLeftUp() = default;

std::pair<float, float> DiagonalBlockLeftUp::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    float ax = position.first;
    float ay = position.second ;//+1;

    float bx = ax + w;
    float by = ay;

    float cx = bx;
    float cy = by - h;
    return this->triangleMatrixPosToCenterOfMass(position, std::make_pair(bx, by),
                                                 std::make_pair(cx, cy));
}