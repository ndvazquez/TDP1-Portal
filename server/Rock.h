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
    b2Body* body;
    Dynamic* actual_movement;

public:
    explicit Rock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    float getVerticalVelocity();
    float getHorizontalVelocity();
    void eliminateGravity();
    void downloadToEarth();
    void moveRight();
    void moveLeft();
    void stop();
    void destroyActualMovement();
    void update();
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ROCK_H