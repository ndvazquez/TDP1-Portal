//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H


#include "StaticObject.h"

class Gate : public StaticObject {
public:
    Gate(std::string& path, Window& window, const std::string& name, int w, int h);
    ~Gate();

    void setName() override;
};


#endif //PORTAL_GATE_H
