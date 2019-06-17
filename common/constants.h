//
// Created by ndv on 5/28/19.
//

#ifndef PORTAL_CONSTANTS_H
#define PORTAL_CONSTANTS_H

enum ChellState {
    IDLE,
    JUMPING,
    DEAD,
    WINNER,
    MOVING_LEFT,
    MOVING_RIGHT
};

enum SwitchState {
    OFF,
    ON
};

enum GateState {
    OPEN,
    CLOSED
};

enum PortalOrientation {
    HORIZONTAL,
    VERTICAL
};

enum PortalType {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    INVALID
};

//Object names
#define METAL_BLOCK_NAME "MetalBlock"
#define DIAGONAL_METAL_BLOCK_NAME "DiagonalMetalBlock"
#define BRICK_BLOCK_NAME "BrickBlock"
#define EB_NAME "EnergyBall"
#define EB_HORIZONTAL_NAME "EnergyBallHorizontal"
#define EB_VERTICAL_NAME "EnergyBallVertical"
#define ET_NAME "EnergyTransmitter"
#define ET_RIGHT_NAME "EnergyTransmitterRight"
#define ET_LEFT_NAME "EnergyTransmitterLeft"
#define ET_UP_NAME "EnergyTransmitterUp"
#define ET_DOWN_NAME "EnergyTransmitterDown"
#define ER_NAME "EnergyReceptor"
#define ER_UP_NAME "EnergyReceptorUp"
#define ER_DOWN_NAME "EnergyReceptorDown"
#define ER_RIGHT_NAME "EnergyReceptorRight"
#define ER_LEFT_NAME "EnergyReceptorLeft"
#define BLUE_SHOT_NAME "BlueShot"
#define ORANGE_SHOT_NAME "OrangeShot"
#define ACID_NAME "Acid"
#define ENERGY_BAR_NAME "EnergyBar"
#define BUTTON_NAME "Button"
#define ROCK_NAME "Rock"
#define CAKE_NAME "Cake"
#define CHELL_NAME "Chell"
#define PORTAL_NAME "Portal"
#define FLOOR_NAME "Floor"
#define GATE_NAME "Gate"
#define PINTOOL_NAME "PinTool"

// Objects sizes.
#define METAL_SIDE 2
#define CHELL_WIDTH 1
#define CHELL_HEIGHT 1.95
#define BUTTON_WIDTH 1
#define BUTTON_HEIGHT 0.5
#define ACID_WIDTH 3
#define ACID_HEIGHT 0.5
#define ROCK_WIDTH 1
#define ROCK_HEIGHT 1
#define BULLET_WIDTH 0.5
#define BULLET_HEIGHT 0.5
#define ENERGY_BALL_WIDTH 1
#define ENERGY_BALL_HEIGHT 1
#define PORTAL_WIDTH 0.5
#define PORTAL_HEIGHT 2
#define CAKE_WIDTH 1
#define CAKE_HEIGHT 1
#define GATE_WIDTH 1
#define GATE_HEIGHT 2
#define CHELL_WHEEL_RADIUS 0.25
#define PINTOOL_HEIGHT 0.5
#define PINTOOL_WIDTH 0.5

// ViewFactory view type codes.
#define CHELL_VIEW_CODE 0
#define ACID_VIEW_CODE 1
#define ENERGY_BALL__VIEW_CODE 2
#define ROCK_VIEW_CODE 3
#define BLUE_PORTAL_VIEW_CODE 4
#define ORANGE_PORTAL_VIEW_CODE 5
#define BUTTON_VIEW_CODE 6
#define BULLET_VIEW_CODE 7
#define CAKE_VIEW_CODE 8
#define GATE_VIEW_CODE 9

// AudioSystem sound codes.
#define RUN_SOUND 0
#define JUMP_SOUND 1
#define PORTAL_GUN_SOUND 2

// AudioSystem song codes.
#define BG_SONG_GAME 0

// Event type codes.
#define USER_QUIT_CODE 0
#define USER_JUMP_CODE 1
#define USER_MOVE_LEFT_CODE 2
#define USER_MOVE_RIGHT_CODE 3
#define USER_STOP_CODE 4
#define USER_BLUE_PORTAL_CODE 5
#define USER_ORANGE_PORTAL_CODE 6
#define USER_GRAB_ROCK 7
#define USER_DROP_ROCK 8
#define USER_THROW_ROCK 9
#define USER_REMOVE_PORTAL 10
#define USER_PINTOOL 11
#define USER_REMOVE_PINTOOL 12

#endif //PORTAL_CONSTANTS_H
