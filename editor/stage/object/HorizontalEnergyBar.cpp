//
// Created by camix on 19/06/19.
//

#include "HorizontalEnergyBar.h"

HorizontalEnergyBar::HorizontalEnergyBar(std::string &path,
                                     Window &window,
                                     int id,
                                     int w,
                                     int h) :
        EnergyBar(path, window, id, w, h) {

    std::cerr << "SOy horizontal y mi ID es: " << id << std::endl;

}

HorizontalEnergyBar::~HorizontalEnergyBar() = default;

void HorizontalEnergyBar::draw(SDL_Rect* rect) {
    std::cerr << "Estoy dibujando una horizontal" << std::endl;
    SDL_Rect newRect = {rect->x, rect->y + rect->h/2, rect->w, rect->h/2};
    StaticObject::draw(&newRect);
}
std::pair<float, float> HorizontalEnergyBar::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(
            position, ENERGY_BAR_HEIGHT, ENERGY_BAR_WIDTH);
}

std::pair<int, int> HorizontalEnergyBar::centerOfMassToMatrixPos(
        const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(
            pair, ENERGY_BAR_HEIGHT, ENERGY_BAR_WIDTH);
}
