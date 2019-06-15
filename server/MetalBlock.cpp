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
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        chell->onFloor(true);
    }
    if (type == "BlueShot") {
        BlueShot* blueShot = static_cast<BlueShot*>(entity);
        Chell* chell = blueShot->getChell();

        float x_pos_metal = getHorizontalPosition();
        float y_pos_metal = getVerticalPosition();

        float side_metal = METAL_SIDE;

        float x_pos_blue = blueShot->getHorizontalPosition();
        float y_pos_blue = blueShot->getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;
        float side_blue = BULLET_HEIGHT;

        bool left_side = x_pos_blue <= x_left - side_blue/2;
        bool right_side = x_pos_blue >= x_right + side_blue/2;
        bool down_side = y_pos_blue <= y_down - side_blue/2;

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
                BluePortal* bluePortal = new BluePortal(coord, true, LEFT);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_right + portal_h_side/2,
                        y_pos_metal);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_right + portal_h_side + ROCK_WIDTH,
                        y_pos_metal);
                BluePortal* bluePortal = new BluePortal(coord, true, RIGHT);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            }
        } else {
            portal_v_side = PORTAL_WIDTH;

            if (down_side) {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_down - portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_down - portal_v_side);
                BluePortal* bluePortal = new BluePortal(coord, false, DOWN);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            } else {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_top + portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_top + portal_v_side + CHELL_HEIGHT);
                BluePortal* bluePortal = new BluePortal(coord, false, UP);
                chell->addBluePortal(bluePortal, coord_to_teleport);
            }
        }
        blueShot->die();
    }
    if (type == "OrangeShot") {
        OrangeShot* orangeShot = static_cast<OrangeShot*>(entity);
        Chell* chell = orangeShot->getChell();

        float x_pos_metal = getHorizontalPosition();
        float y_pos_metal = getVerticalPosition();
        float side_metal = METAL_SIDE;

        float x_pos_orange = orangeShot->getHorizontalPosition();
        float y_pos_orange = orangeShot->getVerticalPosition();

        float x_left = x_pos_metal - side_metal/2;
        float x_right = x_pos_metal + side_metal/2;
        float y_top = y_pos_metal + side_metal/2;
        float y_down = y_pos_metal - side_metal/2;

        float side_blue = BULLET_HEIGHT;

        bool left_side = x_pos_orange <= x_left - side_blue/2;
        bool right_side = x_pos_orange >= x_right + side_blue/2;
        bool down_side = y_pos_orange <= y_down - side_blue/2;

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
                coord_to_teleport = new Coordinate(x_left + portal_h_side + ROCK_WIDTH,
                        y_pos_metal);
                OrangePortal* orangePortal = new OrangePortal(coord, true, RIGHT);
                chell->addOrangePortal(orangePortal, coord_to_teleport);
            }
        } else {
            portal_v_side = PORTAL_WIDTH;
            if (down_side) {
                Coordinate* coord = new Coordinate(x_pos_metal,
                        y_down - portal_v_side/2);
                Coordinate* coord_to_teleport;
                coord_to_teleport = new Coordinate(x_pos_metal,
                        y_down - portal_v_side);
                OrangePortal* orangePortal = new OrangePortal(coord, false, DOWN);
                chell->addOrangePortal(orangePortal, coord_to_teleport);
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

        orangeShot->die();
    }
}
