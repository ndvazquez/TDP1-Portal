//
// Created by camix on 16/06/19.
//

#include <sstream>
#include "LogicGates.h"
#include "../../../common/InputText.h"
#include "InputManager.h"


#define IS_ODD(x) x%2
#define NOT '!'
#define OR " |"
#define AND " &"
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'


LogicGates::LogicGates() = default;

void LogicGates::addNamedElement(Object *obj) {
    namedElements.push_back(obj);
}

void LogicGates::addConditionalElement(Object *obj) {
    conditionalElements.push_back(obj);
}

void LogicGates::setName(Object *obj,
                         std::pair<int, int> position,
                         Window &window,
                         SDL_Rect* rect,
                         SDL_Rect* camera,
                         int yStart,
                         View stageView) {
    if (!obj || !obj->hasName()) return;
    InputManager input(window, "Enter a fucking name", rect);
    std::string& name = input.enteredString(position,
                                            obj,
                                            camera,
                                            yStart,
                                            stageView);
    setName(obj, position, name);
}

void LogicGates::addCondition(Object *obj,
                              std::pair<int, int> position,
                              Window &window,
                              SDL_Rect* rect,
                              SDL_Rect* camera,
                              int yStart,
                              View stageView) {
    if (!obj || !obj->hasCondition()) return;
    InputManager input(window, "Enter a fucking name", rect);
    std::string& condition = input.enteredString(position,
                                            obj,
                                            camera,
                                            yStart,
                                            stageView);
    addCondition(obj, position, condition);
}

void LogicGates::setName(Object *obj, std::pair<int, int> position, std::string newName) {
    try {
        obj->setName(position, newName);
    }
    catch (SetNameException &e) {
        std::cerr << e.what();
    }
}

void LogicGates::addCondition(Object* obj, std::pair<int, int> position, std::string &condition) {
    if(!obj->hasCondition()) {
        return;
    }
    try {
        this->parseCondition(condition);
        obj->addCondition(position, condition);
    } catch (...) {
        return;
    }
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
            for(auto obj : namedElements) {
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

std::map<std::pair<float, float>, std::string> &LogicGates::getNames() {
    names.clear();
    for(auto obj : namedElements) {
        std::map<std::pair<int, int>, std::string>& subNames = obj->getNames();
        for(auto it : subNames) {
            const std::pair<int,int>& position = it.first;
            std::string& name = it.second;
            std::pair<float, float> centerOfMass =
                    obj->matrixPosToCenterOfMass(position);
            names[centerOfMass] = name;
        }
    }
    return names;
}

std::map<std::pair<float, float>, std::string> &LogicGates::getConditions() {
    conditions.clear();
    for(auto obj : conditionalElements) {
        std::map<std::pair<int, int>, std::string>& subConditions =
                                                    obj->getConditions();
        for(auto it : subConditions) {
            const std::pair<int,int>& position = it.first;
            std::string& condition = it.second;
            std::pair<float, float> centerOfMass =
                    obj->matrixPosToCenterOfMass(position);
            conditions[centerOfMass] = condition;
        }
    }
    return conditions;
}
