//
// Created by cecix on 3/06/19.
//

#ifndef PORTAL_ORANGESHOT_H
#define PORTAL_ORANGESHOT_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "entities/Chell.h"
#include "Shot.h"

class OrangeShot: public Shot {
public:
    OrangeShot(b2Body *body, Chell* chell, Coordinate* target);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ORANGESHOT_H
