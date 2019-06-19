//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_DYNAMIC_H
#define PORTAL_DYNAMIC_H

#include <Box2D/Dynamics/b2Body.h>
#include <chrono>
#include "configuration.h"
#include "stage-support/Coordinate.h"
#include "../../common/constants.h"

class Dynamic {
private:
    b2Body* body;
    float energy_ball_impulse;
    std::chrono::system_clock::time_point timeStamp;

    /* Adjusts gravity according to the jump */
    void adjustJump();

public:
    explicit Dynamic(b2Body* body);
    virtual ~Dynamic();

    /* Makes an object jump */
    bool jump(bool chellFloor);

    /* Makes an object move */
    virtual void move(float force);

    /* Makes an object move right */
    void moveRight(float force);

    /* Makes an object move left */
    void moveLeft(float force);

    /* Makes an object stop moving */
    void stop(float force);

    /* Makes an object fly in a horizontal direction */
    void flyHorizontal();

    /* Makes an object fly in a vertical direction */
    void flyVertical();

    /* Makes an object fly in a direction indicated by velocity */
    void fly(b2Vec2 velocity);

    /* Handle collisions of the body against other objects */
    bool handleCollisions();

    /* Makes an object teleport, applicating an extra impulse if neccessary */
    void teleport(Coordinate* coordinate, PortalType type, bool keep_impulse);
};

#endif //PORTAL_DYNAMIC_H
