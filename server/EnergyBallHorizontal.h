//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALLHORIZONTAL_H
#define PORTAL_ENERGYBALLHORIZONTAL_H

#include "EnergyBall.h"

class EnergyBallHorizontal: public EnergyBall {
public:
    explicit EnergyBallHorizontal(b2Body* body);
    virtual void fly() override;
};

#endif //PORTAL_ENERGYBALLHORIZONTAL_H
