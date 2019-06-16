//
// Created by camix on 15/06/19.
//

#include "Receptor.h"

Receptor::Receptor(std::string &path, Window &window, const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool Receptor::hasGravity() {
    return false;
}

void Receptor::addTo(int x, int y, std::map<std::pair<int, int>,
std::string> &tiles, std::string sentinel) {
    Object::addTo(x, y, tiles, RECEPTOR_SENTINEL);
}

Receptor::~Receptor() = default;


void Receptor::setName(std::pair<int, int> position, std::string& enteredName) {
    std::cerr << "Soy un receptor ";
    names[position] = enteredName;
    std::cerr << "y mi nombre es " << enteredName << std::endl;
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

void Receptor::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                        std::unordered_map<std::string, Object *> &textures) {
    names.erase(std::make_pair(x, y));
    Object::removeFrom(x, y, tiles, textures);
}