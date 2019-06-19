//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTORDOWN_H
#define PORTAL_ENERGYRECEPTORDOWN_H


#include "EnergyReceptor.h"

class EnergyReceptorDown: public EnergyReceptor {
public:
    explicit EnergyReceptorDown(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};


#endif //PORTAL_ENERGYRECEPTORDOWN_H
