//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H

#include <Box2D/Dynamics/b2Body.h>

class Acid {
private:
    b2Body* body;

public:
    explicit Acid(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_ACID_H
