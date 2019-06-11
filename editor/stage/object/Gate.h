//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H

#include <map>
#include "StaticObject.h"

class Gate : public StaticObject {
private:
    std::map<std::pair<int, int>, std::string> names;
    std::map<std::string, std::string> conditions;

public:
    Gate(std::string& path, Window& window, const std::string& name, int w, int h);
    ~Gate();

    void setName(std::pair<int, int> position, std::string& enteredName) override;

    void addCondition(std::pair<int, int> position, std::string& condition) override;
};


#endif //PORTAL_GATE_H
