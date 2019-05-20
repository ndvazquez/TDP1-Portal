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

public:
    explicit Rock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    float getVerticalVelocity();
    float getHorizontalVelocity();
    void move();
};

#endif //PORTAL_ROCK_H
