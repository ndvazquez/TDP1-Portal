//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"
#include "Entity.h"

class Rock: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool on_floor;

public:
    explicit Rock(b2Body* body);
    void eliminateGravity();
    void downloadToEarth();
    void moveRight();
    void moveLeft();
    void stop();
    void destroyActualMovement();
    void update();
    void makeStatic();
    void makeDynamic();
    bool isOnFloor();
    bool onFloor(bool onFloor);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ROCK_H
