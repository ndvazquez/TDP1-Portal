//
// Created by camix on 16/06/19.
//

#include "SentinelBlock.h"


SentinelBlock::SentinelBlock(std::string &path, Window &window, const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool SentinelBlock::hasGravity() {
    return false;
}

void SentinelBlock::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                       std::unordered_map<std::string, Object *>& textures) {
}

void SentinelBlock::addTo(int x, int y, std::map<std::pair<int, int>,
        std::string> &tiles, std::unordered_map<std::string,
        Object *> &textures, std::string sentinel) {
}

SentinelBlock::~SentinelBlock() = default;
