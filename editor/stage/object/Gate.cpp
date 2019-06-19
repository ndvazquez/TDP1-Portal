//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Gate.h"

Gate::Gate(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

Gate::~Gate() = default;


void Gate::setName(std::pair<int, int>& position, std::string& enteredName) {
    std::cerr << "Soy una compuerta " << std::endl;
    names[position] = enteredName;
    std::cerr << "y mi nombre es " << enteredName << std::endl;
}

void Gate::addCondition(std::pair<int, int> position, std::string &condition) {
    std::cerr << "Soy una compuerta " << std::endl;
    conditions[position] = condition;

    std::cerr << "mi nombre es: '" << names[position];
    std::cerr << "' y mi condicion es '" << condition << "'" << std::endl;
}


void Gate::removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                      std::unordered_map<int, Object *> &textures) {
    conditions.erase(std::make_pair(x, y));
    names.erase(std::make_pair(x, y));
    Object::removeFrom(x, y, tiles, textures);
}

bool Gate::hasCondition() {
    return true;
}

void Gate::addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles, std::unordered_map<int, Object *> &textures,
                 bool needGravitySentinel) {
    conditions[std::make_pair(x, y)] = "";
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
