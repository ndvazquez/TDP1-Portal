//
// Created by cecix on 18/05/19.
//

#include <string>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>
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
#include "EnergyBar.h"

Chell::Chell(b2Body* body):
        Entity(CHELL_NAME, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    this->actual_state = IDLE;
    body->SetUserData(this);
    chell_is_on_floor = true;
    dead = false;
    rock = nullptr;
    orange_portal = nullptr;
    blue_portal = nullptr;
    blue_portal_to_teleport = nullptr;
    orange_portal_to_teleport = nullptr;
    winner = false;
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == ACID_NAME || type == EB_NAME) {
        die();
        if (type == EB_NAME) {
            static_cast<EnergyBall*>(entity)->die();
        }
    }

    if (type == ROCK_NAME) {
        Rock* rock = static_cast<Rock*>(entity);
        float y_chell = getVerticalPosition();
        float y_rock = rock->getVerticalPosition();
        float vy_rock = rock->getVerticalVelocity();
        if (y_rock > y_chell && vy_rock == 0 && ! rock->isGrabbed()) {
            die();
        }
    }

    if (type == PORTAL_NAME) {
        Portal* portal = static_cast<Portal*>(entity);
        Coordinate* target = portal->getTarget();
        if (target != nullptr) teleport(target, portal->getPortalType());
    }

    if (type == CAKE_NAME) {
        win();
    }

    if (type == ENERGY_BAR_NAME) {
        static_cast<EnergyBar*>(entity)->disableBody();
    }

    if (type == BUTTON_NAME) {
        Button* button = static_cast<Button*>(entity);
        float y_button = button->getVerticalPosition();
        float y_chell = getVerticalPosition();
        if (y_chell > y_button) button->activate();
    }

    chell_is_on_floor = type == METAL_BLOCK_NAME || type == BRICK_BLOCK_NAME
                        || type == DIAGONAL_METAL_BLOCK_NAME || type == FLOOR_NAME
                        || type == ROCK_NAME || type == BUTTON_NAME || type == ET_NAME || type == ER_NAME;
}

void Chell::teleport(Coordinate* coordinate, PortalType type) {
    this->dynamic.teleport(coordinate, type);
}

void Chell::die() {
    this->actual_state = DEAD;
    dead = true;
}

void Chell::win() {
    this->actual_state = WINNER;
    winner = true;
}

bool Chell::isDead() {
    return dead;
}

bool Chell::hasWon() {
    return winner;
}

void Chell::grabRock(Rock* rock) {
    if (this->rock) return;
    Coordinate coord(getHorizontalPosition(), getVerticalPosition());
    rock->elevate(coord);
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
    if (dead || winner) return;
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
    if (chell_is_on_floor) this->actual_state = MOVING_RIGHT;
    if (this->rock) {
        Coordinate coord(getHorizontalPosition(), getVerticalPosition());
        rock->moveRight(coord);
    }
}

void Chell::moveLeft() {
    if (dead || winner) return;
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    if (chell_is_on_floor) this->actual_state = MOVING_LEFT;
    if (this->rock) {
        Coordinate coord(getHorizontalPosition(), getVerticalPosition());
        rock->moveLeft(coord);
    }
}

void Chell::releaseRock() {
    if (this->rock) {
        rock->release();
        rock = nullptr;
    }
}

void Chell::stop() {
    if (dead || winner) return;
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
}

void Chell::jump() {
    if (dead || winner) return;
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

ChellState Chell::getState() {
    return actual_state;
}

void Chell::removePortals() {
    if (this->blue_portal) delete blue_portal;
    if (this->orange_portal) delete orange_portal;
    this->blue_portal = nullptr;
    this->orange_portal = nullptr;
}

void Chell::addOrangePortal(OrangePortal* portal, Coordinate* to_teleport) {
    if (orange_portal != nullptr) delete orange_portal;
    if (orange_portal_to_teleport != nullptr) delete orange_portal_to_teleport;
    orange_portal = portal;
    orange_portal_to_teleport = to_teleport;
}

void Chell::addBluePortal(BluePortal* portal, Coordinate* to_teleport) {
    if (blue_portal != nullptr) delete blue_portal;
    if (blue_portal_to_teleport != nullptr) delete blue_portal_to_teleport;
    blue_portal = portal;
    blue_portal_to_teleport = to_teleport;
}

BluePortal* Chell::getBluePortal() {
    return blue_portal;
}

OrangePortal* Chell::getOrangePortal() {
    return orange_portal;
}

Coordinate* Chell::getBluePortalToTeleport() {
    return blue_portal_to_teleport;
}

Coordinate* Chell::getOrangePortalToTeleport() {
    return orange_portal_to_teleport;
}

Chell::~Chell() {
    destroyActualMovement();
    if (orange_portal != nullptr) delete orange_portal;
    if (blue_portal != nullptr) delete blue_portal;
    if (orange_portal_to_teleport != nullptr) delete orange_portal_to_teleport;
    if (blue_portal_to_teleport != nullptr) delete blue_portal_to_teleport;
}
