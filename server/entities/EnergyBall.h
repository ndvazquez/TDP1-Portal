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
    bool is_vertical;
    Dynamic dynamic;
    std::chrono::system_clock::time_point timeStamp;
    bool is_dead;

public:
    explicit EnergyBall(b2Body* body, bool is_vertical);

    /* An EnergyBall flies */
    void fly();

    /* An EnergyBall dies */
    void die();

    /* Returns a boolean that indicates if an EnergyBall has died */
    bool isDead();

    /* Applies velocity to an EnergyBall in order to change its direction */
    void changeDirection(b2Vec2 velocity);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* An EnergyBall teleports to the location indicated by coordinate */
    void teleport(Coordinate* target, PortalType type);

    /* Checks collisions for EnergyBall */
    void update();
};

#endif //PORTAL_ENERGYBALL_H
