//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <chrono>
#include "Entity.h"

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H

class EnergyBar: public Entity {
public:
    explicit EnergyBar(b2Body* body);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYBAR_H
