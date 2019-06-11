//
// Created by camix on 11/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKUP_H
#define PORTAL_DIAGONALBLOCKUP_H


#include "StaticObject.h"


class DiagonalBlockUp : public StaticObject {
public:
    DiagonalBlockUp(std::string& path, Window& window, const std::string& name, int w, int h);
    ~DiagonalBlockUp();
    bool hasGravity() override;
};


#endif //PORTAL_DIAGONALBLOCKUP_H
