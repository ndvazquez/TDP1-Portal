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

// stage objects id
enum StageObjects {
    EMPTY,
    METAL_BLOCK,
    ROCK_BLOCK,
    LOUNCH_BLOCK_DOWN,
    LOUNCH_BLOCK_UP,
    LOUNCH_BLOCK_LEFT,
    LOUNCH_BLOCK_RIGHT,
    RECEPTOR_DOWN,
    RECEPTOR_UP,
    RECEPTOR_LEFT,
    RECEPTOR_RIGHT,
    DIAGONAL_UP_LEFT,
    DIAGONAL_DOWN_LEFT,
    DIAGONAL_DOWN_RIGHT,
    DIAGONAL_UP_RIGHT,
    ROCK1,
    ROCK2,
    ROCK3,
    CHELL,
    CAKE,
    ACID,
    GATE,
    BUTTON,
    VERTICA_ENERGY_BAR,
    HORIZONTAL_ENERGY_BAR
};

enum Direction {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    INVALID
};

// Stage yaml key
#define STAGE_ATTRIBUTES "Stage"
#define STAGE_SIZE "dimentions"
#define OBJECT_POSITION "position"
#define VERTICAL_SIZE "height"
#define HORIZONTAL_SIZE "width"
#define HORIZONTAL_POSITION "x"
#define VERTICAL_POSITION "y"
#define SATAGE_OBJECTS_NAMES "Names"
#define LOGICAL_GATES "Conditions"
#define OBJECT_NAME "name"
#define SATAGE_OBJECTS_CONDITIONS "condition"

//Object names
#define METAL_BLOCK_NAME "MetalBlock"
#define DIAGONAL_METAL_BLOCK_NAME "DiagonalMetalBlock"
#define DIAGONAL_METAL_BLOCK_45 "DiagonalMetalBlock45"
#define DIAGONAL_METAL_BLOCK_135 "DiagonalMetalBlock135"
#define DIAGONAL_METAL_BLOCK_225 "DiagonalMetalBlock225"
#define DIAGONAL_METAL_BLOCK_315 "DiagonalMetalBlock315"
#define ROCK_BLOCK_NAME "RockBlock"
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
#define BLUE_PORTAL_NAME "BluePortal"
#define ORANGE_PORTAL_NAME "OrangePortal"

// Objects sizes.
#define METAL_SIDE 2
#define CHELL_WIDTH 1
#define CHELL_HEIGHT 1.95
#define BUTTON_WIDTH 2
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
#define ENERGY_BAR_HEIGHT 3
#define ENERGY_BAR_WIDTH 0.5

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

// Protocol stuff
#define THREAD_SUICIDE_PILL "F"
#define REQUEST_LEN_SIZE 4
#define PLAYER_ID_PREFIX "Chell"
#define CREATE_GAME_CODE 0
#define JOIN_GAME_CODE 1
#define SUCCESS_CODE 0
#define FAIL_CODE 1


// Editor metadata yaml keys
#define IMAGE_PATH "path"
#define OBJECT_ID "id"
#define OBJECT_WIDTH "w"
#define OBJECT_HEIGHT "h"

// This should be put in a YAML config file.
#define MTP_FACTOR 70

#endif //PORTAL_CONSTANTS_H