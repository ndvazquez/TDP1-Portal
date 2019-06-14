//
// Created by cecix on 17/05/19.
//

#define rockType "Rock"

#include <string>
#include <iostream>
#include "Rock.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "Stop.h"
#include "MetalBlock.h"
#include "Chell.h"
#include "Button.h"
#include "EnergyBar.h"
#include "BlueShot.h"
#include "OrangeShot.h"
#include <Box2D/Dynamics/b2World.h>


Rock::Rock(b2Body* body):
        Entity(rockType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
    this->dead = false;
    this->teletransported = false;
}

void Rock::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == "Portal") {
        Portal* portal = static_cast<Portal*>(entity);
        Coordinate* target = portal->getTarget();
        if (target != nullptr) {
            teleport(target, portal->getPortalType());
            this->teletransported = true;
        }
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
    if (type == "EnergyBar") {
        die();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "Button") {
        Button* button = static_cast<Button*>(entity);
        float x_button = button->getHorizontalPosition();
        float x_rock = body->GetPosition().x;
        float delta = 0.1;
        if (x_rock > x_button - delta && x_rock < x_button + delta) {
            button->activate();
        }
    }
}

void Rock::elevate(Coordinate& coordinate) {
    body->SetGravityScale(0);
    body->SetTransform(b2Vec2(coordinate.getX() + 1, coordinate.getY()), 0);
}

void Rock::release() {
    activateGravity();
    body->ApplyForce(b2Vec2(0, gameConfiguration.elevationForce),
        body->GetWorldCenter(), true);
}

void Rock::activateGravity() {
    body->SetGravityScale(1);
}

void Rock::moveRight(Coordinate& coordinate) {
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
    body->SetTransform(b2Vec2(coordinate.getX() - 1, coordinate.getY()), 0);
}

void Rock::moveLeft(Coordinate& coordinate) {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    body->SetTransform(b2Vec2(coordinate.getX() + 1, coordinate.getY()), 0);
}

void Rock::stop() {
    float velocity_y = body->GetLinearVelocity().y;
    if (velocity_y >= 0) velocity_y = 0;
    body->SetLinearVelocity(b2Vec2(0, velocity_y));
    destroyActualMovement();
    this->actual_movement = new Stop(body);
}

void Rock::destroyActualMovement() {
    delete this->actual_movement;
}

void Rock::update() {
    dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.rockForce);
   /* if (teletransported) {
        teletransported = false;
        activateGravity();
        body->ApplyLinearImpulse(b2Vec2(0, -gameConfiguration.velocityDownload), body->GetWorldCenter(), true);
    }*/
}

void Rock::downloadToEarth() {
    body->SetGravityScale(1);
    body->ApplyLinearImpulse(b2Vec2(0, -gameConfiguration.velocityDownload), body->GetWorldCenter(), true);
}

void Rock::teleport(Coordinate* target, PortalType type) {
    this->dynamic.teleport(target, type);
}

void Rock::die() {
    dead = true;
}

bool Rock::isDead() {
    return dead;
}
