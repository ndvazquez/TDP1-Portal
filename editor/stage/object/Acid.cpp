//
// Created by camix on 10/06/19.
//

#include "Acid.h"

Acid::Acid(std::string &path, Window &window, int totalFrames, int id, int w, int h) :
        AnimatedObject(path, window, totalFrames, id, w, h) {}

Acid::~Acid() = default;

void Acid::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y + rect->h/2, rect->w, rect->h/2};
    AnimatedObject::draw(&newRect);
}

std::pair<float, float> Acid::matrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(position, ACID_WIDTH, ACID_HEIGHT);
}

std::pair<int, int> Acid::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(pair, ACID_WIDTH, ACID_HEIGHT);
}
