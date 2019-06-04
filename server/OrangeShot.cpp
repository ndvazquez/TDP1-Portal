//
// Created by cecix on 3/06/19.
//

#include "OrangeShot.h"

#define orangeShotType "BlueShot"

#include <string>
#include "OrangeShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

OrangeShot::OrangeShot(b2Body* body, Chell* chell):
        Entity(orangeShotType, body) {
    this->chell = chell;
    body->SetUserData(this);
}

void OrangeShot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock") {


        /*MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        metalBlock->createOrangePortal();
        Coordinate* portalCoordinates = new Coordinate(metalBlock->getHorizontalPosition(),
                                                       metalBlock->getVerticalPosition());
        chell->addOrangePortal(portalCoordinates);*/
    }
    if (type == "DiagonalMetalBlock") {

       /* DiagonalMetalBlock* diagonalBlock =static_cast<DiagonalMetalBlock*>(entity);
        diagonalBlock->createOrangePortal();
        float x_portal_coordinates = diagonalBlock->getHorizontalPosition();
        float y_portal_coordinates = diagonalBlock->getVerticalPosition();
        Coordinate* portalCoordinates = new Coordinate(x_portal_coordinates,
                                                       y_portal_coordinates);
        chell->addOrangePortal(portalCoordinates);*/
    }
}

Chell* OrangeShot::getChell() {
    return chell;
}
