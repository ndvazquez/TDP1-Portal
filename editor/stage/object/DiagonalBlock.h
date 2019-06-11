//
// Created by camix on 11/06/19.
//

#ifndef PORTAL_DIAGONALBLOCK_H
#define PORTAL_DIAGONALBLOCK_H


#include "StaticObject.h"


class DiagonalBlock : public StaticObject {
public:
    DiagonalBlock(std::string& path, Window& window, const std::string& name, int w, int h);
    ~DiagonalBlock();
    bool hasGravity() override;
};


#endif //PORTAL_DIAGONALBLOCK_H
