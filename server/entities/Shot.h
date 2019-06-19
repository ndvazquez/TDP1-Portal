//
// Created by cecix on 3/06/19.
//

#ifndef PORTAL_SHOT_H
#define PORTAL_SHOT_H

#include <string>
#include "Entity.h"
#include "entities/Chell.h"

class Shot: public Entity {
protected:
    Chell* chell;
    Coordinate* target;
    Coordinate* origin;
    bool is_dead;
    Dynamic dynamic;
    float angle;

public:
    Shot(std::string type, b2Body *body, Chell* chell, Coordinate* target);
    ~Shot();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns Chell object asociated to the shot */
    Chell* getChell();

    /* Liberates a bullet */
    void shoot();

    /* Returns a boolean that indicates if the Shot has finished its trajectory */
    bool isDead();

    /* Kills a Shot */
    void die();

    /* Returns the angle of the Shot's trajectory */
    float getAngle();
};

#endif //PORTAL_SHOT_H
