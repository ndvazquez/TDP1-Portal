//
// Created by cecix on 13/05/19.
//
#define diagonalMetalBlockType "DiagonalMetalBlock"

#include "DiagonalMetalBlock.h"
#include "EnergyBall.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

DiagonalMetalBlock::DiagonalMetalBlock(b2Body* body):
    Entity(diagonalMetalBlockType, body) {
    body->SetUserData(this); //to handle collisions
}

void DiagonalMetalBlock::handleCollision(Entity* entity) {
    if (entity->getType() == "EnergyBall") {
        static_cast<EnergyBall*>(entity)->changeDirection();
    }
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
        if (portal) {
            Coordinate* portalCoordinates = new Coordinate(body->GetPosition().x,
                                                           body->GetPosition().y);
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

void DiagonalMetalBlock::createPortal() {
    this->portal = true;
}

void DiagonalMetalBlock::deletePortal() {
    this->portal = false;
}

bool DiagonalMetalBlock::hasPortal() {
    return portal;
}