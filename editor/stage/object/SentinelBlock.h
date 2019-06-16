//
// Created by camix on 16/06/19.
//

#ifndef PORTAL_SENTINELBLOCK_H
#define PORTAL_SENTINELBLOCK_H


#include "StaticObject.h"

class SentinelBlock : public StaticObject {
public:
    SentinelBlock(std::string& path, Window& window, const std::string& name, int w, int h);
    ~SentinelBlock();
    void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                    std::unordered_map<std::string, Object *>& map) override;

    bool hasGravity() override;
    void addTo(int x, int y, std::map<std::pair<int, int>,
            std::string> &tiles, std::unordered_map<std::string,
            Object *>& textures, std::string sentinel = SENTINEL) override;
};


#endif //PORTAL_SENTINELBLOCK_H
