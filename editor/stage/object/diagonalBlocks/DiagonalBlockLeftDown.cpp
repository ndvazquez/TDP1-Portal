//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftDown.h"

DiagonalBlockLeftDown::DiagonalBlockLeftDown(std::string &path, Window &window,
                                    const std::string& name, int w, int h) :
        DiagonalBlockDown(path, window, name, w, h) {}

DiagonalBlockLeftDown::~DiagonalBlockLeftDown() = default;

std::pair<float, float> DiagonalBlockLeftDown::centerOfMass(
                            const std::pair<int, int> &position) {
    float ax = position.first;
    float ay = position.second;

    float bx = ax + w;
    float by = ay;

    float cx = bx;
    float cy = by - h;

    ax = ax;
    ay = ay - h;
    return this->triangleCenterOfMass(std::make_pair(ax, ay),
                                 std::make_pair(bx, by),
                                 std::make_pair(cx, cy));
}