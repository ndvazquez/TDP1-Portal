//
// Created by cecix on 17/05/19.
//

#define buttonType "Button"

#include <string>
#include "Button.h"
#include "Chell.h"

Button::Button(b2Body* body):
    Entity(buttonType, body) {
    body->SetUserData(this);
    this->state = OFF;
}

void Button::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        float x_rock = rock->getHorizontalPosition();
        float x_button = body->GetPosition().x;
        float delta = 0.1;
        if (x_rock > x_button - delta && x_rock < x_button + delta) {
            activate();
        }
    }
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
        float x_chell = chell->getHorizontalPosition();
        float x_button = body->GetPosition().x;
        float delta = 0.1;
        if (x_chell > x_button - delta && x_chell < x_button + delta) {
            activate();
        }
    }
}

void Button::activate() {
    this->state = ON;
}

bool Button::isActive() {
    return this->state == ON;
}

ButtonState Button::getState() {
    return this->state;
}