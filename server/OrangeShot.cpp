//
// Created by cecix on 3/06/19.
//

#include "OrangeShot.h"

#include <string>
#include <iostream>
#include "OrangeShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

OrangeShot::OrangeShot(b2Body *body, Chell* chell, Coordinate* target) :
        Shot(ORANGE_SHOT_NAME, body, chell, target) {
    body->SetUserData(this);
}

void OrangeShot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == PINTOOL_NAME) {
        static_cast<PinTool*>(entity)->die();
    }
    if (type == METAL_BLOCK_NAME) {
        MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);

        float x_pos_metal = metalBlock->getHorizontalPosition();
        float y_pos_metal = metalBlock->getVerticalPosition();
        float side_metal = METAL_SIDE;

        float x_pos_orange = getHorizontalPosition();
        float y_pos_orange = getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;

        bool left_side = x_pos_orange <= x_left;
        bool right_side = x_pos_orange >= x_right;
        bool down_side = y_pos_orange <= y_down;

        float portal_h_side = PORTAL_WIDTH;
        float portal_v_side;

        bool vertical_cond = left_side || right_side;

        if (vertical_cond) {
            if (left_side) {
                Coordinate* coord = new Coordinate(x_left - portal_h_side/2,
                        y_pos_metal);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_left - portal_h_side - ROCK_WIDTH,
                        y_pos_metal);
                OrangePortal* orangePortal = new OrangePortal(coord, true, LEFT);
                chell->addOrangePortal(orangePortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_right + portal_h_side/2,
                        y_pos_metal);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_right + portal_h_side + ROCK_WIDTH,
                        y_pos_metal);
                OrangePortal* orangePortal = new OrangePortal(coord, true, RIGHT);
                chell->addOrangePortal(orangePortal, coord_to_teleport);
            }
        } else {

            portal_v_side = PORTAL_WIDTH;

            if (down_side) {
                Coordinate* coordinate = new Coordinate(x_pos_metal,
                        y_down - portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_down - portal_v_side);
                OrangePortal* oPortal = new OrangePortal(coordinate, false, DOWN);
                chell->addOrangePortal(oPortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_top + portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_top + portal_v_side + CHELL_HEIGHT);
                OrangePortal* orangePortal = new OrangePortal(coord, false, UP);
                chell->addOrangePortal(orangePortal, coord_to_teleport);
            }
        }
    }
    die(); //If the shot collides against something it dies
}

