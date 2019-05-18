//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H

#include <Box2D/Dynamics/b2Body.h>

class Button {
private:
    b2Body* body;

public:
    explicit Button(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};


#endif //PORTAL_BUTTON_H
