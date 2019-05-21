//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H


class EnergyBar {
    b2Body* body;

public:
    explicit EnergyBar(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_ENERGYBAR_H
