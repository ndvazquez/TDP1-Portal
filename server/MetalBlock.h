//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_METALBLOCK_H
#define PORTAL_METALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>

class MetalBlock {
private:
    size_t side;
    b2Body* body;

public:
    MetalBlock(size_t side, b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    size_t getSide();
};

#endif //PORTAL_METALBLOCK_H
