//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_MOVELEFT_H
#define PORTAL_MOVELEFT_H


#include "Dynamic.h"

class MoveLeft: public Dynamic {
public:
    explicit MoveLeft(b2Body* body);
    virtual void move() override;
    virtual ~MoveLeft();
};

#endif //PORTAL_MOVELEFT_H
