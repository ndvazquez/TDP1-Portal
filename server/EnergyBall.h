//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALL_H
#define PORTAL_ENERGYBALL_H

#include <string>
#include "Dynamic.h"
#include "Entity.h"

class EnergyBall: public Entity {
private:
    bool is_vertical;
    Dynamic dynamic;
    std::chrono::system_clock::time_point timeStamp;
    bool is_dead;

public:
    explicit EnergyBall(b2Body* body, bool is_vertical);
    void fly();
    void die();
    bool isDead();
    void changeDirection(b2Vec2 velocity);
    virtual void handleCollision(Entity* entity) override;
    void teleport(Coordinate* target, PortalType type);
    void update();
};


#endif //PORTAL_ENERGYBALL_H
