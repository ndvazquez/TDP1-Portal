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

Chell::Chell(b2Body* body):
        Entity(chellType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    this->actual_state = IDLE;
    body->SetUserData(this);
    chell_is_on_floor = true;
    dead = false;
    rock = nullptr;
    orange_portal = nullptr;
    blue_portal = nullptr;
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

    if (type == "MetalBlock") {
        MetalBlock *metalBlock = static_cast<MetalBlock *>(entity);
        if (metalBlock->hasPortal()) {
            Coordinate *coordinate = new Coordinate(metalBlock->getHorizontalPosition(),
                                                    metalBlock->getVerticalPosition());
            teleport(coordinate);
        }
    }

    if (type == "DiagonalMetalBlock") {
        DiagonalMetalBlock* diagonalBlock = static_cast<DiagonalMetalBlock*>(entity);
        if (diagonalBlock->hasPortal()) {
            Coordinate *coordinate = new Coordinate(diagonalBlock->getHorizontalPosition(),
                                                    diagonalBlock->getVerticalPosition());
            teleport(coordinate);
        }
    }

    chell_is_on_floor = type == "MetalBlock" || type == "BrickBlock"
                        || type == "DiagonalMetalBlock" || type == "Floor";
}

void Chell::teleport(Coordinate* coordinate) {
    if (orange_portal == nullptr || blue_portal == nullptr) return;

    float x_orange = orange_portal->getX();
    float y_orange = orange_portal->getY();
    float x_blue = blue_portal->getX();
    float y_blue = blue_portal->getY();
    float x_coordinate = coordinate->getX();
    float y_coordinate = coordinate->getY();

    if (x_coordinate == x_orange && y_coordinate == y_orange) {
        this->dynamic.teleport(blue_portal);
    }

    else if (x_coordinate == x_blue && y_coordinate == y_blue) {
        this->dynamic.teleport(orange_portal);
    }
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
    if (orange_portal != nullptr) delete orange_portal;
    this->orange_portal = portal;
}

void Chell::addBluePortal(Coordinate* portal) {
    if (blue_portal != nullptr) delete blue_portal;
    this->blue_portal = portal;
}

Coordinate* Chell::getBluePortal() {
    return blue_portal;
}

Coordinate* Chell::getOrangePortal() {
    return orange_portal;
}

Chell::~Chell() {
    destroyActualMovement();
    if (orange_portal != nullptr) delete orange_portal;
    if (blue_portal != nullptr) delete blue_portal;
}
