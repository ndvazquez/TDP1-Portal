//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include <Box2D/Dynamics/b2Body.h>

class Rock {
private:
    b2Body* body;

public:
    Rock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_ROCK_H
