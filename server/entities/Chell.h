//
// Created by cecix on 18/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Dynamics/b2Body.h>
#include "movements/Dynamic.h"
#include "Entity.h"
#include "Rock.h"
#include "../../common/constants.h"
#include "stage-support/Coordinate.h"
#include "Portal.h"
#include <list>
#include <portal-support/PortalHolder.h>
#include "PinTool.h"

class Chell: public Entity {
private:
    Dynamic dynamic;
    Dynamic* actual_movement;
    bool chell_is_on_floor;
    bool dead;
    Rock* rock;
    ChellState actual_state;
    PortalHolder* orange_portal;
    PortalHolder* blue_portal;
    Coordinate* orange_portal_to_teleport;
    Coordinate* blue_portal_to_teleport;
    bool winner;
    PinTool* pintool;

    /* Frees memory allocated for the movement */
    void destroyActualMovement();

public:
    explicit Chell(b2Body* body);
    ~Chell();

    /* Moves Chell in the right direction */
    void moveRight();

    /* Moves Chell in the left direction */
    void moveLeft();

    /* Stops Chell's movement */
    void stop();

    /* Chell jumps */
    void jump();

    /* Updates Chell's state through movement */
    void update();

    /* Returns boolean that indicates if Chell is in the ground */
    bool inGround();

    /* Kills Chell */
    void die();

    /* Chell wins */
    void win();

    /* Returns boolean that indicates if Chell has died */
    bool isDead();

    /* Returns boolean that indicates if Chell has won */
    bool hasWon();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Updates Chell state on floor */
    void onFloor(bool onFloor);

    /* Chell grabs a rock */
    void grabRock(Rock* rock);

    /* Chell realeases a rock */
    void releaseRock();

    /* Chell downloads a rock to earth */
    void downloadRock();

    /* Saves the orange portal made by Chell and its corresponding
     * location to teleport */
    void addOrangePortal(PortalHolder* orangePortal, Coordinate* to_teleport);

    /* Saves the blue portal made by Chell and its corresponding
     * location to teleport */
    void addBluePortal(PortalHolder* bluePortal, Coordinate* to_teleport);

    /* Saves the pintool made by Chell */
    void addPinTool(PinTool* pintool);

    /* Chell teleports to the location indicated by coordinate */
    void teleport(Coordinate* coordinate, Direction type);

    /* Chell resets portals */
    void removePortals();

    /* Returns Chell actual state */
    ChellState getState();

    /* Returns blue portal made by Chell */
    PortalHolder* getBluePortal();

    /* Returns orange portal made by Chell */
    PortalHolder* getOrangePortal();

    /* Returns the coordinate of the blue portal */
    Coordinate* getBluePortalToTeleport();

    /* Returns the coordinate of the orange portal */
    Coordinate* getOrangePortalToTeleport();

    /* Returns the pintool made by Chell */
    PinTool* getPinTool();
};

#endif //PORTAL_CHELL_H
