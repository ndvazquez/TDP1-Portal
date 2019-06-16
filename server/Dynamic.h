//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H

#include <Box2D/Dynamics/b2Body.h>
#include <chrono>
#include "configuration.h"
#include "Coordinate.h"
#include "../common/constants.h"

class Dynamic {
private:
    b2Body* body;
    float energy_ball_impulse;
    std::chrono::system_clock::time_point timeStamp;

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
    void fly(b2Vec2 velocity);
    bool handleCollisions();
    void teleport(Coordinate* coordinate, PortalType type);
};

#endif //PORTAL_DYNAMIC_H
