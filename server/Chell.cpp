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
#include "../editor/Chell.h"
#include "Rock.h"
#include "Portal.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "BlueShot.h"

Chell::Chell(b2Body* body):
        Entity(chellType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    this->actual_state = IDLE;
    body->SetUserData(this);
    chell_is_on_floor = true;
    dead = false;
    rock = nullptr;
    orangePortal = nullptr;
    bluePortal = nullptr;
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        if (rock->getVerticalVelocity() < -0 && ! rock->isOnFloor()) {
            die();
        }
        rock->makeStatic();
    }

    if (type == "Acid" || type == "EnergyBall") {
        die();
    }
    if (type == "Portal") {
        Coordinate* coordinate = static_cast<Portal*>(entity)->getOtherPortal();
        teleport(coordinate);
    }

    if (type == "MetalBlock") {
        std::cout << "holisssss" << std::endl;}
        /*
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        if (metalBlock->hasPortal()) {
            //teletransportar
        }
        Coordinate* coordinate = static_cast<Portal*>(entity)->getOtherPortal();
        teleport(coordinate);*/
    /*}
    if (type == "DiagonalMetalBlock") {
        DiagonalMetalBlock* diagonalBlock = static_cast<DiagonalMetalBlock*>(entity);
        if (diagonalBlock->hasPortal()) {
            //teletransportar
        }
        Coordinate* coordinate = static_cast<Portal*>(entity)->getOtherPortal();
        teleport(coordinate);
    }*/

    chell_is_on_floor = type == "MetalBlock" || type == "BrickBlock"
                        || type == "DiagonalMetalBlock" || type == "Floor";
}

void Chell::teleport(Coordinate* coordinate) { //Ojo que esas son las coordenas del portal chocante
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
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
    if (chell_is_on_floor) this->actual_state = MOVING_RIGHT;
    if (this->rock) rock->moveRight();
}

void Chell::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    if (chell_is_on_floor) this->actual_state = MOVING_LEFT;
    if (this->rock) rock->moveLeft();
}

void Chell::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
    if (! chell_is_on_floor) {
        this->actual_state = JUMPING;
    } else {
        this->actual_state = IDLE;
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
    if (chell_is_on_floor) this->dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.chellForce);
    if (this->rock) rock->update();
}

void Chell::jump() {
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


Chell::~Chell() {
    destroyActualMovement();
}
