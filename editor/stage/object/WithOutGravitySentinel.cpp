//
// Created by camix on 16/06/19.
//

#include "WithOutGravitySentinel.h"


WithOutGravitySentinel::WithOutGravitySentinel(std::string &path, Window &window,
                                               int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool WithOutGravitySentinel::hasGravity() {
    return false;
}

void WithOutGravitySentinel::removeFrom(int x, int y,
                                        std::map<std::pair<int, int>, int> &tiles,
                                        std::unordered_map<int, Object *> &textures) {
    // you can't be removed on your own. U does not exist by your own.
}


void WithOutGravitySentinel::draw(SDL_Rect *rec) {
    // do nothing, you are just a sentinel
}

void WithOutGravitySentinel::addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                                   std::unordered_map<int, Object *> &textures, bool needGravitySentinel) {
    //you can't be added on your own. U does not exist by your own.
}

std::pair<float, float> WithOutGravitySentinel::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(
            position, METAL_SIDE, METAL_SIDE);
}

std::pair<int, int> WithOutGravitySentinel::centerOfMassToMatrixPos(
        const std::pair<float, float> &pair) {
        return this->rectangleCenterOfMassToMatrixPos(
                pair, METAL_SIDE, METAL_SIDE);
}

WithOutGravitySentinel::~WithOutGravitySentinel() = default;
