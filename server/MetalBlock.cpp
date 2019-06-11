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
    this->vertical_portal = false;
    this->horizontal_portal = false;
    this->other = nullptr;
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
    }
    if (type == "Rock") {
        /*Rock* rock = static_cast<Rock*>(entity);
        Coordinate* target = getOtherPortal();
        if (target != nullptr) {
            rock->activateGravity();
            rock->teleport(target);
        }*/ // TODO: watch this
    }
    if (type == "BlueShot") {
        BlueShot* blueShot = static_cast<BlueShot*>(entity);
        Chell* chell = blueShot->getChell();

        float x_pos_metal = getHorizontalPosition();
        float y_pos_metal = getVerticalPosition();
        float side_metal = 2;

        float x_pos_blue = blueShot->getHorizontalPosition();
        float y_pos_blue = blueShot->getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;
        float side_blue = 1;

        bool left_side = x_pos_blue <= x_left - side_blue/2;
        bool right_side = x_pos_blue >= x_right + side_blue/2;
        bool down_side = y_pos_blue <= y_down - side_blue/2;

        float portal_h_side = 1;
        float portal_v_side = 2;

        bool vertical_cond = left_side || right_side;

        if (vertical_cond) {
            std::cout << "Se creo un portal horizontal azul" << std::endl;

            if (left_side) {
                chell->addBluePortal(new Coordinate(x_left - portal_h_side/2, y_pos_metal));
            } else {
                chell->addBluePortal(new Coordinate(x_right + portal_h_side/2, y_pos_metal));
            }
        } else {
            std::cout << "Se creo un portal vertical azul" << std::endl;

            if (down_side) {
                chell->addBluePortal(new Coordinate(x_pos_metal, y_down - portal_v_side/2));
            } else {
                chell->addBluePortal(new Coordinate(x_pos_metal, y_top + portal_v_side/2));
            }
        }
        blueShot->die();
    }
    if (type == "OrangeShot") {
        OrangeShot* orangeShot = static_cast<OrangeShot*>(entity);
        Chell* chell = orangeShot->getChell();

        float x_pos_metal = getHorizontalPosition();
        float y_pos_metal = getVerticalPosition();
        float side_metal = 2;

        float x_pos_orange = orangeShot->getHorizontalPosition();
        float y_pos_orange = orangeShot->getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;
        float side_blue = 1;

        bool left_side = x_pos_orange <= x_left - side_blue/2;
        bool right_side = x_pos_orange >= x_right + side_blue/2;
        bool down_side = y_pos_orange <= y_down - side_blue/2;

        float portal_h_side = 1;
        float portal_v_side = 2;

        bool vertical_cond = left_side || right_side;

        if (vertical_cond) {
            std::cout << "Se creo un portal horizontal naranja" << std::endl;

            if (left_side) {
                chell->addOrangePortal(new Coordinate(x_left - portal_h_side/2, y_pos_metal));
            } else {
                chell->addOrangePortal(new Coordinate(x_right + portal_h_side/2, y_pos_metal));
            }
        } else {
            std::cout << "Se creo un portal vertical naranja" << std::endl;

            if (down_side) {
                chell->addOrangePortal(new Coordinate(x_pos_metal, y_down - portal_v_side/2));
            } else {
                chell->addOrangePortal(new Coordinate(x_pos_metal, y_top + portal_v_side/2));
            }
        }

        orangeShot->die();
    }
}
