//
// Created by cecix on 9/06/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H


#include <Box2D/Dynamics/b2Body.h>
#include "Button.h"
#include <unordered_map>
#include <string>

class Gate {
private:
    b2Body* body;
    std::string logic;
    std::unordered_map<std::string, Button*> buttons;

public:
    Gate(b2Body* body, std::string logic,
            std::unordered_map<std::string, Button*> buttons);
};


#endif //PORTAL_GATE_H
