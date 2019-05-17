//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_METALBLOCK_H
#define PORTAL_METALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>

class MetalBlock {
private:
    b2Body* body;

public:
    MetalBlock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_METALBLOCK_H
