//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_PHYSICSWORLD_H
#define PORTAL_PHYSICSWORLD_H

#include <Box2D/Dynamics/b2World.h>
#include "entities/Floor.h"
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
    ~PhysicsWorld();

    /* Adds an static rectangle of a given dimention to the world */
    b2Body* addStaticRectangle(float v_side, float h_side,
                               float x_pos, float y_pos);

    /* Adds a dynamic rectangle of a given dimention to the world */
    b2Body* addDynamicRectangle(float v_side, float h_side,
                                float x_pos, float y_pos);

    /* Adds a dynamic rectangle of a given dimention with two
     * wheels on the bottom to the world */
    b2Body* addDynamicRectangleWithWheels(float v_side, float h_side,
            float x_pos, float y_pos);

    /* Adds an static triangle of a given dimention to the world */
    b2Body* addTriangle(float side, float x_pos, float y_pos, float angle);

    /* Destroys a given body in the world */
    void destroyBody(b2Body* body);

    /* Returns a boolean indicating if a b2Body exists in the world */
    bool hasObject(b2Body* body);

    /* Simulates step in Box2D */
    void step();
};

#endif //PORTAL_PHYSICSWORLD_H
