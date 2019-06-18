//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockRightDown.h"

DiagonalBlockRightDown::DiagonalBlockRightDown(std::string &path, Window &window,
                                               int id, int w, int h) :
        DiagonalBlockDown(path, window, id, w, h) {}

DiagonalBlockRightDown::~DiagonalBlockRightDown() = default;

std::pair<float, float> DiagonalBlockRightDown::MatrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    float ax = position.first;
    float ay = position.second;

    float bx = ax;
    float by = ay - h;

    float cx = bx + w;
    float cy = by;
    return this->triangleCenterOfMass(std::make_pair(ax, ay),
                                      std::make_pair(bx, by),
                                      std::make_pair(cx, cy));
}