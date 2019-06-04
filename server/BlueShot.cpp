//
// Created by cecix on 2/06/19.
//

#define blueShotType "BlueShot"

#include <string>

#include <iostream>
#include "BlueShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

BlueShot::BlueShot(b2Body *body, Chell* chell, Coordinate* target) :
    Shot(blueShotType, body, chell, target) {
    body->SetUserData(this);
}

void BlueShot::handleCollision(Entity* entity) {
    die(); //If the shot collides against something it dies
    std::string type = entity->getType();
    if (type == "MetalBlock") {
        /*MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        metalBlock->createBluePortal();
        Coordinate* portalCoordinates = new Coordinate(metalBlock->getHorizontalPosition(),
                                        metalBlock->getVerticalPosition());
        chell->addBluePortal(portalCoordinates);*/
    }
    if (type == "DiagonalMetalBlock") {

       /* DiagonalMetalBlock* diagonalBlock =static_cast<DiagonalMetalBlock*>(entity);
        diagonalBlock->createBluePortal();
        float x_portal_coordinates = diagonalBlock->getHorizontalPosition();
        float y_portal_coordinates = diagonalBlock->getVerticalPosition();
        Coordinate* portalCoordinates = new Coordinate(x_portal_coordinates,
                                                       y_portal_coordinates);
        chell->addBluePortal(portalCoordinates);*/
    }
}



