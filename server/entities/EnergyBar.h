//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <chrono>
#include "Entity.h"
#include "../../common/constants.h"

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H

class EnergyBar: public Entity {
private:
    Orientation orientation;
public:
    EnergyBar(b2Body* body, Orientation orientation);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns orientation */
    Orientation getOrientation();
};

#endif //PORTAL_ENERGYBAR_H
