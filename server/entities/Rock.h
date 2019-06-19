//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include "movements/Dynamic.h"
#include "Entity.h"

class Rock: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool dead;
    bool grabbed;

    /* Frees memory allocated for the movement */
    void destroyActualMovement();

    /* Activates the body's gravity */
    void activateGravity();

public:
    explicit Rock(b2Body* body);

    /* Elevates a rock to a given coordinates */
    void elevate(Coordinate& coordinate);

    /* Downloads a rock to the ground */
    void downloadToEarth();

    /* A Rock moves right */
    void moveRight(Coordinate& coordinate);

    /* A Rock moves left */
    void moveLeft(Coordinate& coordinate);

    /* A Rock stops moving */
    void stop();

    /* Updates Rock's state through movement */
    void update();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* A Rock teleports to the location indicated by coordinate */
    void teleport(Coordinate* target, PortalType type);

    /* A Rock is released upwards */
    void release();

    /* Returns a boolean that indicates that a Rock has died */
    bool isDead();

    /* Kills a Rock*/
    void die();

    /* Returns a boolean that indicates if a rock is being grabbed */
    bool isGrabbed();
};

#endif //PORTAL_ROCK_H
