//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"

class Rock {
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
    void makeBouncement();
    void moveRight();
    void moveLeft();
    void stop();
    void destroyActualMovement();
    void update();
};

#endif //PORTAL_ROCK_H
