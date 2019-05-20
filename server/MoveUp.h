//
// Created by cecix on 20/05/19.
//

#ifndef PORTAL_MOVEUP_H
#define PORTAL_MOVEUP_H

#include "Dynamic.h"

class MoveUp: public Dynamic {
public:
    explicit MoveUp(b2Body* body);
    virtual void move(float force) override;
    virtual ~MoveUp();
};

#endif //PORTAL_MOVEUP_H
