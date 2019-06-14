//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include "Dynamic.h"
#include "Entity.h"

class Rock: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool dead;
    bool teletransported;

public:
    explicit Rock(b2Body* body);
    void elevate(Coordinate& coordinate);
    void downloadToEarth();
    void moveRight(Coordinate& coordinate);
    void moveLeft(Coordinate& coordinate);
    void stop();
    void destroyActualMovement();
    void update();
    virtual void handleCollision(Entity* entity) override;
    void teleport(Coordinate* target, PortalType type);
    void release();
    void activateGravity();
    bool isDead();
    void die();
};

#endif //PORTAL_ROCK_H
