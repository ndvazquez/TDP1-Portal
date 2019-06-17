//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKRIGHTDOWN_H
#define PORTAL_DIAGONALBLOCKRIGHTDOWN_H


#include "DiagonalBlockDown.h"

class DiagonalBlockRightDown : public DiagonalBlockDown {
public:
    DiagonalBlockRightDown(std::string& path, Window& window, const std::string& name, int w, int h);
    ~DiagonalBlockRightDown();
    std::pair<float, float> centerOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_DIAGONALBLOCKRIGHTDOWN_H
