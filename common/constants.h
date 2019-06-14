//
// Created by ndv on 5/28/19.
//

#ifndef PORTAL_CONSTANTS_H
#define PORTAL_CONSTANTS_H

enum ChellState {
    IDLE,
    JUMPING,
    DEAD,
    MOVING_LEFT,
    MOVING_RIGHT,
    WINNER
};

enum ButtonState {
    ON,
    OFF
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

// AudioSystem sound codes.
#define RUN_SOUND 0
#define JUMP_SOUND 1

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

#endif //PORTAL_CONSTANTS_H
