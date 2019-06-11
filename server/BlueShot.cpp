//
// Created by cecix on 2/06/19.
//

#define blueShotType "BlueShot"

#include <string>

#include <iostream>
#include "BlueShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

BlueShot::BlueShot(b2Body *body, Chell* chell, Coordinate* target) :
    Shot(blueShotType, body, chell, target) {
    body->SetUserData(this);
}

void BlueShot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock") {
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        float x_pos_metal = metalBlock->getHorizontalPosition();
        float y_pos_metal = metalBlock->getVerticalPosition();
        float side_metal = 2;

        float x_pos_blue = getHorizontalPosition();
        float y_pos_orange = getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;
        float side_blue = 1;

        bool left_side = x_pos_blue <= x_left - side_blue/2;
        bool right_side = x_pos_blue >= x_right + side_blue/2;
        bool down_side = y_pos_orange <= y_down - side_blue/2;

        float portal_h_side = 0.5;
        float portal_v_side = 2;

        bool vertical_cond = left_side || right_side;

        if (vertical_cond) {
            if (left_side) {
                Coordinate* coord = new Coordinate(x_left - portal_h_side/2,
                        y_pos_metal);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_left - portal_h_side,
                        y_pos_metal);
                BluePortal* bluePortal = new BluePortal(coord, true);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_right + portal_h_side/2,
                        y_pos_metal);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_left + portal_h_side,
                        y_pos_metal);
                BluePortal* bluePortal = new BluePortal(coord, true);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            }
        } else {
            if (down_side) {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_down - portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_down - portal_v_side);
                BluePortal* bluePortal = new BluePortal(coord, false);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_top + portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_top + portal_v_side);
                BluePortal* bluePortal = new BluePortal(coord, false);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            }
        }
    }
    die(); //If the shot collides against something it dies
}
