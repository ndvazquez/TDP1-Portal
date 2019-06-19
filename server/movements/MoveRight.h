//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_MOVERIGHT_H
#define PORTAL_MOVERIGHT_H


#include "Dynamic.h"

class MoveRight: public Dynamic {
public:
    explicit MoveRight(b2Body* body);
    virtual void move(float force) override;
    virtual ~MoveRight();
};

#endif //PORTAL_MOVERIGHT_H
