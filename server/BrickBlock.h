//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCK_H
#define PORTAL_BRICKBLOCK_H

#include <Box2D/Dynamics/b2Body.h>

class BrickBlock {
private:
    b2Body* body;

public:
    BrickBlock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_BRICKBLOCK_H
