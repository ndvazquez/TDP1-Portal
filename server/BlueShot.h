//
// Created by cecix on 2/06/19.
//

#ifndef PORTAL_BLUESHOT_H
#define PORTAL_BLUESHOT_H


#include <Box2D/Dynamics/b2Body.h>
#include "Chell.h"

class BlueShot: public Entity {
private:
    Chell* chell;
    Coordinate* target;
    bool is_dead;

public:
    BlueShot(b2Body *body, Chell* chell, Coordinate* target);
    virtual void handleCollision(Entity* entity) override;
    Chell* getChell();
    void shoot();
    bool isDead();
    void setExactPosition();
};


#endif //PORTAL_BLUESHOT_H
