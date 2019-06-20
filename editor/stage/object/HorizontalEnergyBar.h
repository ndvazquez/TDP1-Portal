//
// Created by camix on 19/06/19.
//

#ifndef PORTAL_HORIZONTALENERGYBAR_H
#define PORTAL_HORIZONTALENERGYBAR_H


#include "EnergyBar.h"

class HorizontalEnergyBar : public EnergyBar {
public:
    HorizontalEnergyBar(std::string &path, Window &window, int id, int w, int h);
    ~HorizontalEnergyBar();
    std::pair<float, float> matrixPosToCenterOfMass(
            const std::pair<int, int> &position) override;

    std::pair<int, int> centerOfMassToMatrixPos(
            const std::pair<float, float> &pair) override;

    void draw(SDL_Rect *rect) override;
};


#endif //PORTAL_HORIZONTALENERGYBAR_H
