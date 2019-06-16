//
// Created by camix on 16/06/19.
//

#ifndef PORTAL_LOGICGATES_H
#define PORTAL_LOGICGATES_H

#include <string>
#include <map>
#include "object/Object.h"
#include "object/Gate.h"


#define INVALID_CONDITION_EXC "Invalid condition\n"

class LogicGates {
private:
    std::vector<Object*> namedElements;
    std::map<std::pair<int, int>, std::string> names;
    std::map<std::pair<int, int>, std::string> conditions;

public:
    LogicGates();
    void addElement(Object* obj);
    void setName(Object* obj, std::pair<int, int> position, std::string newName);
    void addCondition(Object* obj, std::pair<int, int> position, std::string &condition);

    void parseCondition(std::string &condition);
};

class StageControllerInvalidConditionException : public std::exception  {
public:
    const char* what() const noexcept override {
        return INVALID_CONDITION_EXC;
    }
};

#endif //PORTAL_LOGICGATES_H
