//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENTITY_H
#define PORTAL_ENTITY_H

#include <string>
#include <Box2D/Dynamics/b2Body.h>

class Entity {
protected:
    const std::string type;
    b2Body* body;

public:
    Entity(std::string type, b2Body* body);

    /* Returns the type of an Entity */
    const std::string& getType();

    /* Handles collision against other objects in the world */
    virtual void handleCollision(Entity* entity) = 0;

    /* Returns the x component of the body's position */
    float getHorizontalPosition();

    /* Returns the y component of the body's position */
    float getVerticalPosition();

    /* Returns the x component of the body's velocity */
    float getHorizontalVelocity();

    /* Returns the y component of the body's velocity */
    float getVerticalVelocity();

    /* Returns a pointer to the body */
    b2Body* getBody();
};

#endif //PORTAL_ENTITY_H
