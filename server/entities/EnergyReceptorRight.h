//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTORRIGHT_H
#define PORTAL_ENERGYRECEPTORRIGHT_H

#include "EnergyReceptor.h"

class EnergyReceptorRight: public EnergyReceptor {
public:
    explicit EnergyReceptorRight(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYRECEPTORRIGHT_H
