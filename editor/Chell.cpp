//
// Created by camix on 22/05/19.
//

#include "Chell.h"

Chell::Chell(const std::string &path, Window &window, int totalFrames) :
        AnimatedObject(path, window, totalFrames) {}

Chell::~Chell() = default;

bool Chell::canBeOn() {
    return false;
}