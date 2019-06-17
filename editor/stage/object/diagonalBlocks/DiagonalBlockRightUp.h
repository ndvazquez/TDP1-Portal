//
// Created by camix on 11/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKRIGHTUP_H
#define PORTAL_DIAGONALBLOCKRIGHTUP_H


#include "../StaticObject.h"
#include "DiagonalBlockUp.h"



class DiagonalBlockRightUp : public DiagonalBlockUp {
public:
    DiagonalBlockRightUp(std::string &path, Window &window, int id, int w, int h);
    ~DiagonalBlockRightUp();
    std::pair<float, float> centerOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_DIAGONALBLOCKRIGHTUP_H
