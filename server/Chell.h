//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

//#define chellForce 15

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"

class Chell {
private:
    Dynamic dynamic;
    b2Body* body;
    Dynamic* actual_movement;

public:
    explicit Chell(b2Body* body);
    ~Chell();

    void moveRight();
    void moveLeft();
    void stop();
    void jump(float y0);
    void destroyActualMovement();
    void update();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
    bool inGround(float y0);
};

#endif //PORTAL_CHELL_H
