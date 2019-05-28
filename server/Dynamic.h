//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H

#include <Box2D/Dynamics/b2Body.h>
#include "configuration.h"

class Dynamic {
private:
    b2Body* body;
    float energy_ball_impulse;

public:
    explicit Dynamic(b2Body* body);
    virtual ~Dynamic();
    void adjustJump();
    bool jump(bool chellFloor);
    virtual void move(float force);
    void moveRight(float force);
    void moveLeft(float force);
    void stop(float force);
    void flyHorizontal();
    void flyVertical();
    bool isColliding();
    void downloadToEarth();
    bool handleCollisions();
    void eliminateGravity();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};

#endif //PORTAL_DYNAMIC_H
