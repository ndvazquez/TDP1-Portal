//
// Created by cecix on 3/06/19.
//

#ifndef PORTAL_ORANGESHOT_H
#define PORTAL_ORANGESHOT_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "Chell.h"

class OrangeShot: public Entity {
private:
    Chell* chell;
public:
    OrangeShot(b2Body* body, Chell* chell);
    virtual void handleCollision(Entity* entity) override;
    Chell* getChell();
};

#endif //PORTAL_ORANGESHOT_H
