//
// Created by camix on 16/06/19.
//

#include <sstream>
#include "LogicGates.h"
#include "../../common/InputText.h"
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
    try {
        if (!obj || !obj->hasName()) return;
        InputManager input(window, "ENTER A NAME", rect);
        std::string &name = input.startReading(position,
                                               obj,
                                               camera,
                                               yStart,
                                               stageView);
        setName(obj, position, name);
    } catch (SetNameException &e) {
        std::string error = e.what();
        OutputText out(window, error.c_str());
        out.writeTheScreen(error);
    }
}
#define INVALID_CONDITION_MESSAGE1 "APPARENTLY YOU ENTERED AN INVALID CONDITION."
#define INVALID_CONDITION_MESSAGE2 "I REALLY DO NOT KNOW WHY IS INVALID. YOU KNOW IT?"
#define INVALID_CONDITION_MESSAGE3 "NEVER MIND. IT'S A MYSTERY I'LL SOLVE LATER..."
#define INVALID_CONDITION_MESSAGE4 "BY MYSELF..."
#define INVALID_CONDITION_MESSAGE5 "BECAUSE YOU WILL BE DEAD."

void LogicGates::addCondition(Object *obj,
                              std::pair<int, int> position,
                              Window &window,
                              SDL_Rect* rect,
                              SDL_Rect* camera,
                              int yStart,
                              View stageView) {
    try {
        if (!obj || !obj->hasCondition()) return;
        InputManager input(window, "ENTER A CONDITION", rect);
        std::string &condition = input.startReading(position,
                                                    obj,
                                                    camera,
                                                    yStart,
                                                    stageView);
        addCondition(obj, position, condition);
    } catch (StageControllerInvalidConditionException& e) {
        OutputText out(window, INVALID_CONDITION_MESSAGE1);
        std::string message = INVALID_CONDITION_MESSAGE1;
        out.writeTheScreen(message);
        message = INVALID_CONDITION_MESSAGE2;
        out.writeTheScreen(message);
        message = INVALID_CONDITION_MESSAGE3;
        out.writeTheScreen(message);
        message = INVALID_CONDITION_MESSAGE4;
        out.writeTheScreen(message);
        message = INVALID_CONDITION_MESSAGE5;
        out.writeTheScreen(message);
    }
}

void LogicGates::setName(Object *obj, std::pair<int, int> position, std::string newName) {
    try {
        obj->setName(position, newName);
    }
    catch (SetNameException &e) {
        __throw_exception_again;
    }
}

void LogicGates::addCondition(Object* obj, std::pair<int, int> position, std::string &condition) {
    try {
        if(!obj->hasCondition()) return;
        this->parseCondition(condition);
        obj->addCondition(position, condition);
    } catch (StageControllerInvalidConditionException) {
        __throw_exception_again;
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
                throw StageControllerInvalidConditionException();
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
            throw StageControllerInvalidConditionException();
        }
        i++;
    }

    if (IS_ODD(i)) {
        return;
    } else {
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
