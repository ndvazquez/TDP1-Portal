//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H


#include <Box2D/Dynamics/b2Body.h>

class Dynamic {
private:
    b2Body* body;

public:
    Dynamic(b2Body* body);
    ~Dynamic();
    float getHorizontalPosition();
    float getVerticalPosition();
    void moveRight();
    void moveLeft();
    void stop();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};

#endif //PORTAL_DYNAMIC_H
