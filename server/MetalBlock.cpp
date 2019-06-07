//
// Created by cecix on 13/05/19.
//

#define metalBlockType "MetalBlock"

#include <string>
#include <iostream>
#include "MetalBlock.h"
#include "Chell.h"
#include "OrangeShot.h"
#include "BlueShot.h"

MetalBlock::MetalBlock(b2Body* body):
    Entity(metalBlockType, body) {
    body->SetUserData(this);
    this->portal = false;
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
        if (portal) {
            float x = body->GetPosition().x;
            float y = body->GetPosition().y;
            Coordinate* portalCoordinates = new Coordinate(x, y);
            chell->teleport(portalCoordinates);
        }
    }
    if (type == "BlueShot") {
        BlueShot* blueShot = static_cast<BlueShot*>(entity);
        Chell* chell = blueShot->getChell();
        createPortal();
        Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                                                       body->GetPosition().y);
        chell->addBluePortal(portalCoordinates);
        blueShot->die();
    }
    if (type == "OrangeShot") {
        OrangeShot* orangeShot = static_cast<OrangeShot*>(entity);
        Chell* chell = orangeShot->getChell();
        createPortal();
        Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                                        body->GetPosition().y);
        chell->addOrangePortal(portalCoordinates);
        orangeShot->die();
    }
}

void MetalBlock::createPortal() {
    this->portal = true;
}

void MetalBlock::deletePortal() {
    this->portal = false;
}

bool MetalBlock::hasPortal() {
    return portal;
}
