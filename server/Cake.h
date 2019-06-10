//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H


#include "Entity.h"

class Cake: public Entity {
public:
    explicit Cake(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};


#endif //PORTAL_CAKE_H
