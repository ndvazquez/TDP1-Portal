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
#include "OrangePortal.h"
#include "BluePortal.h"
#include <list>

class Chell: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool chell_is_on_floor;
    bool dead;
    Rock* rock;
    ChellState actual_state;
    OrangePortal* orange_portal;
    BluePortal* blue_portal;
    Coordinate* orange_portal_to_teleport;
    Coordinate* blue_portal_to_teleport;
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
    void releaseRock();
    void downloadRock();
    void addOrangePortal(OrangePortal* orangePortal, Coordinate* to_teleport);
    void addBluePortal(BluePortal* bluePortal, Coordinate* to_teleport);
    void teleport(Coordinate* coordinate);
    ChellState getState();
    BluePortal* getBluePortal();
    OrangePortal* getOrangePortal();
    Coordinate* getBluePortalToTeleport();
    Coordinate* getOrangePortalToTeleport();
};

#endif //PORTAL_CHELL_H
