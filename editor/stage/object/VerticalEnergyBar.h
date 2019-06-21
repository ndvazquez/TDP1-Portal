//
// Created by camix on 19/06/19.
//

#ifndef PORTAL_VERTICALENERGYBAR_H
#define PORTAL_VERTICALENERGYBAR_H


#include "EnergyBar.h"

class VerticalEnergyBar : public EnergyBar {
public:
    VerticalEnergyBar(std::string &path, Window &window, int id, int w, int h);
    ~VerticalEnergyBar();
    std::pair<float, float> matrixPosToCenterOfMass(
            const std::pair<int, int> &position) override;

    std::pair<int, int> centerOfMassToMatrixPos(
            const std::pair<float, float> &pair) override;

    void draw(SDL_Rect *rect) override;
};


#endif //PORTAL_VERTICALENERGYBAR_H
