//
// Created by camix on 28/05/19.
//

#include "Cake.h"
#include <iostream>

Cake::Cake(std::string& path, Window& window, int totalFrames ,const std::string& name, int w, int h) :
        AnimatedObject(path, window, totalFrames, name, w, h) {}

Cake::~Cake() = default;
