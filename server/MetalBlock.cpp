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
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
        /*if (portal) {
            Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                    body->GetPosition().y);
            chell->teleport(portalCoordinates);
        }*/
    }
    if (type == "Rock") {
        static_cast<Rock*>(entity)->onFloor(true);
    }
    if (type == "BlueShot") {
        /*
        BlueShot* blueShot = static_cast<BlueShot*>(entity);
        Chell* chell = blueShot->getChell();
        createPortal(); //TODO: Maybe this isn't valid
        Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                                                       body->GetPosition().y);
        chell->addBluePortal(portalCoordinates);*/
    }
    if (type == "OrangeShot") {
        std::cout << "Orange Shot" << std::endl;
        /*OrangeShot* orangeShot = static_cast<OrangeShot*>(entity);
        Chell* chell = orangeShot->getChell();
        createPortal(); //TODO: Maybe this isn't valid'
        Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                                        body->GetPosition().y);
        chell->addOrangePortal(portalCoordinates);*/
    }
}

void MetalBlock::createPortal() {
    this->portal = true;
}

bool MetalBlock::hasPortal() {
    return portal;
}