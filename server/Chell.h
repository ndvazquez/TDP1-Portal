//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Dynamics/b2Body.h>
#include "Dynamic.h"
#include "Entity.h"
#include "Rock.h"
#include "../common/constants.h"
#include "Coordinate.h"
#include "Portal.h"
#include <list>

class Chell: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool chell_is_on_floor;
    bool dead;
    Rock* rock;
    State actual_state;
    Coordinate* orange_portal;
    Coordinate* blue_portal;
    bool winner;

public:
    explicit Chell(b2Body* body);
    ~Chell();

    void moveRight();
    void moveLeft();
    void stop();
    void jump();
    void destroyActualMovement();
    void update();
    bool inGround();
    void die();
    void win();
    bool isDead();
    bool hasWon();
    virtual void handleCollision(Entity* entity) override;
    void onFloor(bool onFloor);
    void grabRock(Rock* rock);
    void downloadRock();
    void addOrangePortal(Coordinate* coordinate);
    void addBluePortal(Coordinate* coordinate);
    void teleport(Coordinate* coordinate);
    State getState();
    Coordinate* getBluePortal();
    Coordinate* getOrangePortal();
};

#endif //PORTAL_CHELL_H
