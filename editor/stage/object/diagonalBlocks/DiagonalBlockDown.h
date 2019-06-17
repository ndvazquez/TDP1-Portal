//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKDOWN_H
#define PORTAL_DIAGONALBLOCKDOWN_H


#include "../StaticObject.h"

class DiagonalBlockDown : public StaticObject{
public:
    DiagonalBlockDown(std::string &path, Window &window, int id, int w, int h);
    ~DiagonalBlockDown();
    bool hasGravity() override;
};


#endif //PORTAL_DIAGONALBLOCKDOWN_H
