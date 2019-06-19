//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <chrono>
#include "Entity.h"

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H

class EnergyBar: public Entity {
private:
    std::chrono::system_clock::time_point timeStamp;

public:
    explicit EnergyBar(b2Body* body);

    /* Chell teleports to the location indicated by coordinate */
    void handleCollision(Entity* entity) override;

    /* Makes body invisible for all objects */
    void disableBody();

    /* Makes body visible for all objects */
    void activateBody();
};

#endif //PORTAL_ENERGYBAR_H
