//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCK_H
#define PORTAL_BRICKBLOCK_H

#include <Box2D/Dynamics/b2Body.h>

class BrickBlock {
private:
    size_t side;
    b2Body* body;

public:
    BrickBlock(size_t side, b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    size_t getSide();
};

#endif //PORTAL_BRICKBLOCK_H
