//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALL_H
#define PORTAL_ENERGYBALL_H

#include <string>
#include "movements/Dynamic.h"
#include "Entity.h"

class EnergyBall: public Entity {
private:
    Dynamic dynamic;
    std::chrono::system_clock::time_point timeStamp;
    bool is_dead;
    Direction eb_type;

public:
    EnergyBall(b2Body* body, Direction eb_type);

    /* An EnergyBall flies */
    void fly();

    /* An EnergyBall dies */
    void die();

    /* Returns a boolean that indicates if an EnergyBall has died */
    bool isDead();

    /* Changes orientation of an EnergyBall */
    void applyOrientation(Direction direction);

    /* Inverts orientation of an EnergyBall */
    void invertDirection();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* An EnergyBall teleports to the location indicated by coordinate */
    void teleport(Coordinate* target, Direction type);

    /* Returns the actual direction of an EnergyBall */
    Direction getDirection();

    /* Checks collisions for EnergyBall */
    void update();
};

#endif //PORTAL_ENERGYBALL_H
