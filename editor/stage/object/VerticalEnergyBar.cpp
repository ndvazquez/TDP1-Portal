//
// Created by camix on 19/06/19.
//

#include "VerticalEnergyBar.h"


VerticalEnergyBar::VerticalEnergyBar(std::string &path,
                                     Window &window,
                                     int id,
                                     int w,
                                     int h) :
        EnergyBar(path, window, id, w, h) {

}

VerticalEnergyBar::~VerticalEnergyBar() = default;

void VerticalEnergyBar::draw(SDL_Rect* rect) {
    std::cerr << "Estoy dibujando una vertical" << std::endl;
    SDL_Rect newRect = {rect->x, rect->y, rect->w/2, rect->h};
    StaticObject::draw(&newRect);
}
std::pair<float, float> VerticalEnergyBar::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(
            position, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT);
}

std::pair<int, int> VerticalEnergyBar::centerOfMassToMatrixPos(
        const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(
            pair, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT);
}
