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
    float ax = position.first;
    float ay = position.second;

    float bx = ax;
    float by = ay - h;

    float cx = bx + w;
    float cy = by;
    return this->triangleMatrixPosToCenterOfMass(std::make_pair(ax, ay),
                                                 std::make_pair(bx, by),
                                                 std::make_pair(cx, cy));
}

std::pair<int, int> DiagonalBlockRightDown::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    float x = pair.first;
    float y = pair.second;

    std::cerr << "\n\nEstoy donde quiero:" << std::endl;

    std::pair<int, int> a(x - (-1.0/3)  * w - 1, y - (-2.0/3) * h);

    std::cerr << "\t(w,h) = (" << w << ", " << h << ")" << std::endl;
    std::cerr << "\ta = (" << a.first << ", " << a.second << ")" << std::endl;
    return a;
}
