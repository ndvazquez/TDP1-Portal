//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_PHYSICSWORLD_H
#define PORTAL_PHYSICSWORLD_H

#include <Box2D/Dynamics/b2World.h>
#include "Floor.h"
#include "Box2D/Box2D.h"

class WorldOutOfRangeException : public std::exception {
    virtual const char* what() const throw() {
        std::string message = "This object doesn't fit in the stage!\n";
        return message.c_str();
    }
};

class PhysicsWorld {
private:
    b2World* world;
    size_t width;
    size_t height;
    Floor* floor;

public:
    PhysicsWorld(b2World* world, size_t width, size_t height);
    b2Body* addStaticRectangle(float v_side, float h_side,
                               float x_pos, float y_pos);
    b2Body* addDynamicRectangle(float v_side, float h_side,
                                float x_pos, float y_pos);
    b2Body* addDynamicRectangleWithWheels(float v_side, float h_side,
            float x_pos, float y_pos);
    b2Body* addTriangle(float side, float x_pos, float y_pos, float angle);
    void destroyBody(b2Body* body);
    bool hasObject(b2Body* body);
    void step();
    ~PhysicsWorld();
};

#endif //PORTAL_PHYSICSWORLD_H
