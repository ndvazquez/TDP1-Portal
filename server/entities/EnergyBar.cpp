//
// Created by cecix on 17/05/19.
//

#define energyBarType "EnergyBar"

#include <Box2D/Dynamics/b2Fixture.h>
#include "EnergyBar.h"
#include "BlueShot.h"
#include "OrangeShot.h"

EnergyBar::EnergyBar(b2Body *body):
    Entity(ENERGY_BAR_NAME, body) {
    this->body->SetUserData(this);

    //Setting the category and mask bits
    b2Fixture* fixture = body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0x0010;
    filter.maskBits = 0xFF00;
    fixture->SetFilterData(filter);
}

void EnergyBar::handleCollision(Entity *entity) {
    const std::string& type = entity->getType();
    if (type == ROCK_NAME) {
        dynamic_cast<Rock*>(entity)->die();
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}
