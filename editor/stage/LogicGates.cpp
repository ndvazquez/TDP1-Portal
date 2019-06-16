//
// Created by camix on 16/06/19.
//

#include <sstream>
#include "LogicGates.h"


#define IS_ODD(x) x%2
#define NOT '!'
#define OR " |"
#define AND " &"
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'


LogicGates::LogicGates() = default;

void LogicGates::addElement(Object* obj) {
    namedElements.push_back(obj);
}


void LogicGates::setName(Object *obj, std::pair<int, int> position, std::string newName) {
    obj->setName(position, newName);
}

void LogicGates::addCondition(Object* obj, std::pair<int, int> position, std::string &condition) {
    if(!obj->hasCondition()) {
        return;
    }
    try {
        this->parseCondition(condition);
    } catch (...) {
        return;
    }
    obj->addCondition(position, condition);
}

void LogicGates::parseCondition(std::string &condition) {
    std::istringstream iss(condition);
    std::string word;
    bool allGood;
    int i = 0;
    while (iss >> word) {
        if (IS_ODD(i)) { //it is a button name
            allGood = word != AND && word != OR;
            if (!allGood) {
                std::cerr << "Parece que no es & o |. Es: " << word << std::endl;
            }
        } else {
            if (word[0] == NOT or word[0] == OPEN_BRACKET) {
                word = word.substr(1);
            }
            if (word.back() == CLOSE_BRACKET) {
                word.pop_back();
            }
            allGood = false;
            for(auto it = namedElements.begin(); it != namedElements.end(); it++) {
                Object* obj = *it;
                allGood ^= obj->doesThisNameExist(word);
            }

        }
        if (!allGood) {
            std::cerr << "NOT ALL GOOD" << std::endl;
            throw StageControllerInvalidConditionException();
        }
        i++;
    }

    if (IS_ODD(i)) {
        return;
    } else {
        std::cerr << "NOT THE CORRECT NUMBER" << std::endl;
        throw StageControllerInvalidConditionException();
    }
}
