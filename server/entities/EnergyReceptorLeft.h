//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTORLEFT_H
#define PORTAL_ENERGYRECEPTORLEFT_H

#include "EnergyReceptor.h"

class EnergyReceptorLeft: public EnergyReceptor {
public:
    explicit EnergyReceptorLeft(b2Body* body);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYRECEPTORLEFT_H
