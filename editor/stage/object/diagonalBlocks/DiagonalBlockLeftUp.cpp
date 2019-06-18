//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockLeftUp.h"

DiagonalBlockLeftUp::DiagonalBlockLeftUp(std::string &path, Window &window,
                                         int id, int w, int h) :
        DiagonalBlockUp(path, window, id, w, h) {}

std::pair<int, int> DiagonalBlockLeftUp::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return std::pair<int, int>();
}

DiagonalBlockLeftUp::~DiagonalBlockLeftUp() = default;

std::pair<float, float> DiagonalBlockLeftUp::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    return std::pair<int, int>();
}