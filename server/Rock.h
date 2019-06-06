//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H

#include "Dynamic.h"
#include "Entity.h"

class Rock: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;

public:
    explicit Rock(b2Body* body);
    void elevate();
    void downloadToEarth();
    void moveRight();
    void moveLeft();
    void stop();
    void destroyActualMovement();
    void update();
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ROCK_H
