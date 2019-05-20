//
// Created by cecix on 20/05/19.
//

#ifndef PORTAL_MOVEDOWN_H
#define PORTAL_MOVEDOWN_H

#include "Dynamic.h"

class MoveDown: public Dynamic {
public:
    explicit MoveDown(b2Body* body);
    virtual void move(float force) override;
    virtual ~MoveDown();
};

#endif //PORTAL_MOVEDOWN_H
