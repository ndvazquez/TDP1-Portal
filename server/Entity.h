//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENTITY_H
#define PORTAL_ENTITY_H

#include <string>
#include <Box2D/Dynamics/b2Body.h>

class Entity {
protected:
    std::string type;
    b2Body* body;

public:
    Entity(std::string type, b2Body* body);
    std::string getType();
    virtual void handleCollision(Entity* entity) = 0;
    float getVerticalVelocity();
    float getHorizontalVelocity();
    float getHorizontalPosition();
    float getVerticalPosition();
    b2Body* getBody();
};


#endif //PORTAL_ENTITY_H
