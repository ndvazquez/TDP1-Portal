//
// Created by cecix on 17/05/19.
//

#include <string>
#include "Button.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

Button::Button(b2Body* body):
    Entity(BUTTON_NAME, body), dynamic(body) {
    body->SetUserData(this);
    this->state = OFF;
}

void Button::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        float y_rock = rock->getVerticalPosition();
        float y_button = getVerticalPosition();
        if (y_rock > y_button) activate();
    } else if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
        float y_chell = chell->getVerticalPosition();
        float y_button = getVerticalPosition();
        if (y_chell > y_button) activate();
    } else {
        desactivate();
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
}

void Button::activate() {
    this->state = ON;
}
void Button::desactivate() {
    this->state = OFF;
}

bool Button::isActive() {
    return this->state == ON;
}

SwitchState Button::getState() {
    return this->state;
}

void Button::update() {
    if (! dynamic.handleCollisions()) {
        desactivate();
    }
}
