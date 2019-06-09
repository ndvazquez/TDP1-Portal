//
// Created by cecix on 18/05/19.
//

#define chellType "Chell"

#include <string>
#include <iostream>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include "Chell.h"
#include "MoveRight.h"
#include "Stop.h"
#include "MoveLeft.h"
#include "../editor/stage/object/Chell.h"
#include "Rock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "BlueShot.h"
#include "EnergyBall.h"
#include "Button.h"

Chell::Chell(b2Body* body):
        Entity(chellType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    this->actual_state = IDLE;
    body->SetUserData(this);
    chell_is_on_floor = true;
    dead = false;
    rock = nullptr;
    portal = new Portal();
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Acid" || type == "EnergyBall") {
        die();
        if (type == "EnergyBall") {
            static_cast<EnergyBall*>(entity)->die();
        }
    }

    if (type == "MetalBlock") {
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        Coordinate* target = metalBlock->getOtherPortal();
        if (target != nullptr) this->dynamic.teleport(target);
    }

    if (type == "Button") {
        Button* button = static_cast<Button*>(entity);
        float x_button = button->getHorizontalPosition();
        float x_chell = body->GetPosition().x;
        float delta = 0.1;
        if (x_chell > x_button - delta && x_chell < x_button + delta) {
            button->activate();
        }
    }

    chell_is_on_floor = type == "MetalBlock" || type == "BrickBlock"
                        || type == "DiagonalMetalBlock" || type == "Floor"
                        || type == "Rock" || type == "Button";
}

void Chell::teleport(Coordinate* coordinate) {
    this->dynamic.teleport(coordinate);
}

void Chell::die() {
    this->actual_state = DEAD;
    dead = true;
}

bool Chell::isDead() {
    return dead;
}

void Chell::grabRock(Rock* rock) {
    if (this->rock) return;
    rock->elevate();
    this->rock = rock;
}

void Chell::downloadRock() {
    if (! rock) return;
    rock->downloadToEarth();
    rock = nullptr;
}

void Chell::onFloor(bool onFloor) {
    chell_is_on_floor = onFloor;
}

void Chell::moveRight() {
    if (dead) return;
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
    if (chell_is_on_floor) this->actual_state = MOVING_RIGHT;
    if (this->rock) rock->moveRight();
}

void Chell::moveLeft() {
    if (dead) return;
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    if (chell_is_on_floor) this->actual_state = MOVING_LEFT;
    if (this->rock) rock->moveLeft();
}

void Chell::stop() {
    if (dead) return;
    destroyActualMovement();
    this->actual_movement = new Stop(body);
    if (! chell_is_on_floor) {
        this->actual_state = JUMPING;
    } else {
        this->actual_state = IDLE;
        body->SetLinearVelocity(b2Vec2(0, 0));
    }
    if (this->rock) rock->stop();
}

void Chell::destroyActualMovement() {
    delete this->actual_movement;
}

void Chell::update() {
    chell_is_on_floor = inGround();
    if (chell_is_on_floor && actual_state == JUMPING){
        this->stop();
    }
    if (chell_is_on_floor && ! isDead()) this->dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.chellForce);
    if (this->rock) rock->update();
}

void Chell::jump() {
    if (dead) return;
    bool resul = this->dynamic.jump(chell_is_on_floor);
    if (resul) {
        actual_state = JUMPING;
        chell_is_on_floor = false;
    }
}

bool Chell::inGround() {
    float epsilon = pow(10, -7);
    bool chell_is_still = body->GetLinearVelocity().y < epsilon
                        && body->GetLinearVelocity().y > -epsilon;
    if (chell_is_still) dynamic.handleCollisions();
    return chell_is_on_floor;
}

State Chell::getState() {
    return actual_state;
}

void Chell::addOrangePortal(Coordinate* portal) {
    this->portal->addOrangePortal(portal);
}

void Chell::addBluePortal(Coordinate* portal) {
    this->portal->addBluePortal(portal);
}

Coordinate* Chell::getBluePortal() {
    return portal->getBluePortal();
}

Coordinate* Chell::getOrangePortal() {
    return portal->getOrangePortal();
}

Chell::~Chell() {
    destroyActualMovement();
    delete portal;
}
