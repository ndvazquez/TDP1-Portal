//
// Created by cecix on 3/06/19.
//

#include "OrangeShot.h"

#define orangeShotType "OrangeShot"

#include <string>
#include <iostream>
#include "OrangeShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

OrangeShot::OrangeShot(b2Body *body, Chell* chell, Coordinate* target) :
        Shot(orangeShotType, body, chell, target) {
    body->SetUserData(this);
}

void OrangeShot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock") {
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);

        float x_pos_metal = metalBlock->getHorizontalPosition();
        float y_pos_metal = metalBlock->getVerticalPosition();
        float side_metal = 2;

        float x_pos_orange = getHorizontalPosition();
        float y_pos_orange = getVerticalPosition();

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
    }
    die(); //If the shot collides against something it dies
}

