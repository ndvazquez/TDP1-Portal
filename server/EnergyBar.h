//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H


class EnergyBar: public Entity {
public:
    explicit EnergyBar(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void disableBody();
};

#endif //PORTAL_ENERGYBAR_H
