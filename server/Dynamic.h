//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H

#define initialVelocity 4

#include <Box2D/Dynamics/b2Body.h>

class Dynamic {
private:
    b2Body* body;

public:
    explicit Dynamic(b2Body* body);
    virtual ~Dynamic();
    float getHorizontalPosition();
    float getVerticalPosition();
    virtual void move();
    void jump(float y0);
    void moveRight();
    void moveLeft();
    void stop();
    void fly(float velocity);
    bool isColliding();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};

#endif //PORTAL_DYNAMIC_H
