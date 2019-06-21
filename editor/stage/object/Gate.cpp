//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Gate.h"

Gate::Gate(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

Gate::~Gate() = default;


void Gate::setName(std::pair<int, int>& position, std::string& enteredName) {
    names[position] = enteredName;
}

void Gate::addCondition(std::pair<int, int> position, std::string &condition) {
    conditions[position] = condition;
}


void Gate::removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                      std::unordered_map<int, Object *> &textures) {
    auto conditionsIt = conditions.find(std::make_pair(x, y));
    lastCondition = conditionsIt->second;
    conditions.erase(conditionsIt);
    auto namesIt = names.find(std::make_pair(x, y));
    lastName = namesIt->second;
    names.erase(namesIt);
    Object::removeFrom(x, y, tiles, textures);
}

bool Gate::hasCondition() {
    return true;
}

void Gate::addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles, std::unordered_map<int, Object *> &textures,
                 bool needGravitySentinel) {
    conditions[std::make_pair(x, y)] = lastCondition;
    names[std::make_pair(x, y)] = lastName;
    Object::addTo(x, y, tiles, textures);
}

std::pair<float, float> Gate::matrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(position, GATE_WIDTH, GATE_HEIGHT);
}

std::map<std::pair<int, int>, std::string> &Gate::getNames() {
    return names;
}

std::pair<int, int> Gate::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(pair, GATE_WIDTH, GATE_HEIGHT);
}

std::map<std::pair<int, int>, std::string> &Gate::getConditions() {
    return conditions;
}

bool Gate::hasName() {
    return true;
}
