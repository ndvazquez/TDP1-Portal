//
// Created by camix on 15/06/19.
//

#include "Receptor.h"

Receptor::Receptor(std::string &path, Window &window, int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool Receptor::hasGravity() {
    return false;
}

Receptor::~Receptor() = default;


void Receptor::setName(std::pair<int, int>& position, std::string& enteredName) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if (it->second == enteredName && it->first != position) {
            throw SetNameException();
        }
    }
    names[position] = enteredName;
}

bool Receptor::doesThisNameExist(std::string &string) {
    auto it = this->names.begin();
    for(; it != this->names.end(); it++) {
        if (it->second == string) {
            return true;
        }
    }
    return false;
}

void Receptor::removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                          std::unordered_map<int, Object *> &textures) {
    auto it = names.find(std::make_pair(x, y));
    lastName = it->second;
    names.erase(it);
    Object::removeFrom(x, y, tiles, textures);
}

std::pair<float, float> Receptor::matrixPosToCenterOfMass(const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(position, METAL_SIDE, METAL_SIDE);
}

std::map<std::pair<int, int>, std::string> &Receptor::getNames() {
    return names;
}

void
Receptor::addTo(int x, int y,
        std::map<std::pair<int, int>, int> &tiles,
        std::unordered_map<int, Object *> &textures,
                bool needGravitySentinel) {
    names[std::make_pair(x, y)] = lastName;
    Object::addTo(x, y, tiles, textures);
}

std::pair<int, int> Receptor::centerOfMassToMatrixPos(const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(pair, METAL_SIDE, METAL_SIDE);
}

bool Receptor::hasName() {
    return true;
}

