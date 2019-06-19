//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class Acid: public Entity {
public:
    explicit Acid(b2Body* body);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ACID_H
