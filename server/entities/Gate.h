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

public:
    Gate(b2Body* body, std::string logic,
            std::unordered_map<std::string, ItemActivable*> items);
    void update();
    bool parseBool();
    virtual void handleCollision(Entity* entity) override;
    GateState getState();
};


#endif //PORTAL_GATE_H
