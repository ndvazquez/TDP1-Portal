//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"

class Chell {
private:
    Dynamic dynamic;
    size_t actual_movement; //0 stopped, 1 right, 2 left

public:
    Chell(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    void moveRight();
    void moveLeft();
    void stop();
    void update();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};

#endif //PORTAL_CHELL_H
