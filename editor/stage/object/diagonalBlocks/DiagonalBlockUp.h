//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKUP_H
#define PORTAL_DIAGONALBLOCKUP_H


#include "../StaticObject.h"

class DiagonalBlockUp : public StaticObject {
public:
    DiagonalBlockUp(std::string &path, Window &window, int id, int w, int h);
    ~DiagonalBlockUp();
    bool hasGravity() override;
    void addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles, std::unordered_map<int, Object *> &texturesL, bool needGravitySentinel = false) override;
};


#endif //PORTAL_DIAGONALBLOCKUP_H
