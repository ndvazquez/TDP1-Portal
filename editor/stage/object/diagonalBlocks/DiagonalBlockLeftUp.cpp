//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftUp.h"

DiagonalBlockLeftUp::DiagonalBlockLeftUp(std::string &path, Window &window,
                                         int id, int w, int h) :
        DiagonalBlockUp(path, window, id, w, h) {}

DiagonalBlockLeftUp::~DiagonalBlockLeftUp() = default;

std::pair<float, float> DiagonalBlockLeftUp::centerOfMass(
                                    const std::pair<int, int> &position) {
    float ax = position.first;
    float ay = position.second ;//+1;

    float bx = ax + w;
    float by = ay;

    float cx = bx;
    float cy = by - h;
    return this->triangleCenterOfMass(position, std::make_pair(bx,by),
                                         std::make_pair(cx,cy));
}