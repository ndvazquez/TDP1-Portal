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
    float ax = position.first;
    float ay = position.second;

    float bx = ax + w;
    float by = ay;

    float cx = bx;
    float cy = by - h;

    ax = ax;
    ay = ay - h;
    return this->triangleMatrixPosToCenterOfMass(std::make_pair(ax, ay),
                                                 std::make_pair(bx, by),
                                                 std::make_pair(cx, cy));
}

std::pair<int, int> DiagonalBlockLeftDown::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;
    return std::pair<int, int> (x - (1.0/3) * w, y - (1.0/3) * h + 1);
}
