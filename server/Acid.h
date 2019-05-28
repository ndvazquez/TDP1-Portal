//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class Acid: public Entity {
private:
    b2Body* body;

public:
    explicit Acid(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ACID_H
