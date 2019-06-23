//
// Created by camix on 16/06/19.
//

#include "GravitySentinel.h"


GravitySentinel::GravitySentinel(std::string &path, Window &window,
                                 int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool GravitySentinel::hasGravity() {
    return true;
}

void GravitySentinel::removeFrom(int x, int y,
                                 std::map<std::pair<int, int>, int> &tiles,
                                 std::unordered_map<int, Object *> &textures) {
    // you can't be removed on your own. U does not exist by your own.
}

void GravitySentinel::draw(SDL_Rect *rec) {
    // do nothing, you are just a sentinel
}

void GravitySentinel::addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                            std::unordered_map<int, Object *> &textures, bool needGravitySentinel) {
    //you can't be added on your own. U does not exist by your own.
}

std::pair<float, float> GravitySentinel::matrixPosToCenterOfMass(
        const std::pair<int, int> &position) {
    return this->rectangleMatrixPosToCenterOfMass(
            position, METAL_SIDE, METAL_SIDE);
}

std::pair<int, int> GravitySentinel::centerOfMassToMatrixPos(
        const std::pair<float, float> &pair) {
    return this->rectangleCenterOfMassToMatrixPos(
            pair, METAL_SIDE, METAL_SIDE);
}

GravitySentinel::~GravitySentinel() = default;
