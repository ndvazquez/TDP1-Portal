//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"
#include "Entity.h"

class Chell: public Entity {
private:
    Dynamic dynamic;
    b2Body* body;
    Dynamic* actual_movement;
    bool chell_is_on_floor;

public:
    explicit Chell(b2Body* body);
    ~Chell();

    void moveRight();
    void moveLeft();
    void stop();
    void jump();
    void destroyActualMovement();
    void update();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
    bool inGround();
    virtual void handleCollision(Entity* entity) override;
    void onFloor(bool onFloor);
};

#endif //PORTAL_CHELL_H
