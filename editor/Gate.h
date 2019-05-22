//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H


#include "StaticObject.h"

class Gate : public StaticObject {
public:
    Gate(std::string& path, Window& window);
    ~Gate();
    bool canBeOn() override;
};


#endif //PORTAL_GATE_H
