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
    std::string type = entity->getType();
    if (type == "MetalBlock") {
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        metalBlock->createPortal();
        float x = metalBlock->getHorizontalPosition();
        float y = metalBlock->getVerticalPosition();
        Coordinate* portalCoordinates = new Coordinate(x, y);
        chell->addBluePortal(portalCoordinates);
    }
    if (type == "DiagonalMetalBlock") {
        DiagonalMetalBlock* diagonalBlock;
        diagonalBlock = static_cast<DiagonalMetalBlock*>(entity);
        diagonalBlock->createPortal();
        float x = diagonalBlock->getHorizontalPosition();
        float y = diagonalBlock->getVerticalPosition();
        Coordinate* portalCoordinates = new Coordinate(x, y);
        chell->addBluePortal(portalCoordinates);
    }
    die(); //If the shot collides against something it dies
}



