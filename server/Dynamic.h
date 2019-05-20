//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H


#include <Box2D/Dynamics/b2Body.h>

class Dynamic {
private:
    b2Body* body;
    float impulse;

public:
    explicit Dynamic(b2Body* body);
    virtual ~Dynamic();
    virtual void move();
    void jump();
    void moveRight();
    void moveLeft();
    void stop();
    void flyHorizontal();
    void flyVertical();
    bool isColliding();
    bool handleCollisions();
    void moveRock();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};

#endif //PORTAL_DYNAMIC_H