//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTORUP_H
#define PORTAL_ENERGYRECEPTORUP_H

#include "EnergyReceptor.h"

class EnergyReceptorUp: public EnergyReceptor {
public:
    explicit EnergyReceptorUp(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYRECEPTORUP_H
