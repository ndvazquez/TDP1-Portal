//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_DIAGONALMETALBLOCK_H
#define PORTAL_DIAGONALMETALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>

class DiagonalMetalBlock {
private:
    size_t side;
    b2Body* body;

public:
    DiagonalMetalBlock(size_t side, b2Body* body);
};


#endif //PORTAL_DIAGONALMETALBLOCK_H
