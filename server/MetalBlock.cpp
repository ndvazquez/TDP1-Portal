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
    this->other = nullptr;
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        Coordinate* target = getOtherPortal();
        if (target != nullptr) chell->teleport(target);
        chell->onFloor(true);

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

void MetalBlock::addOtherPortal(MetalBlock* other) {
    this->other = other;
}

Coordinate* MetalBlock::getOtherPortal() {
    if (other == nullptr) return nullptr;
    float x = other->getHorizontalPosition();
    float y = other->getVerticalPosition();
    Coordinate* other = new Coordinate(x, y);
    return other;
}