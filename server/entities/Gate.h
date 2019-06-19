//
// Created by cecix on 9/06/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H

#include <Box2D/Dynamics/b2Body.h>
#include "entities/Button.h"
#include "ItemActivable.h"
#include <unordered_map>
#include <string>
#include <chrono>

class Gate: public Entity {
private:
    std::string logic;
    std::string replaced;
    std::unordered_map<std::string, ItemActivable*> items;
    GateState state;

    /* Returns a boolean that indicates the result of a boolean expression */
    bool parseBool();

public:
    Gate(b2Body* body, std::string logic,
            std::unordered_map<std::string, ItemActivable*> items);

    /* Updates state of the gate (open and close)
     * evaluating the boolean condition */
    void update();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns the state of the gate */
    GateState getState();
};

#endif //PORTAL_GATE_H
