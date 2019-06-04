//
// Created by cecix on 3/06/19.
//

#ifndef PORTAL_SHOT_H
#define PORTAL_SHOT_H

#include "Entity.h"
#include "Chell.h"

class Shot: public Entity {
protected:
    Chell* chell;
    Coordinate* target;
    Coordinate* origin;
    bool is_dead;
    bool to_be_dead;

public:
    Shot(std::string type, b2Body *body, Chell* chell, Coordinate* target);
    virtual void handleCollision(Entity* entity) override;
    Chell* getChell();
    void shoot();
    bool isDead();
    void setExactPosition();
};


#endif //PORTAL_SHOT_H
