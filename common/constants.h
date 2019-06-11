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

//
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
#define PORTAL_WIDTH 1
#define PORTAL_HEIGHT 2
#define CAKE_WIDTH 1
#define CAKE_HEIGHT 1

// ViewFactory view type codes.
#define CHELL_VIEW_CODE 0
#define ACID_VIEW_CODE 1
#define ENERGY_BALL__VIEW_CODE 2
#define ROCK_VIEW_CODE 3
#define PORTAL_VIEW_CODE 4
#define BUTTON_VIEW_CODE 5
#define BULLET_VIEW_CODE 6
#define CAKE_VIEW_CODE 7

// AudioSystem sound codes.
#define RUN_SOUND 0
#define JUMP_SOUND 1

// AudioSystem song codes.
#define BG_SONG_GAME 0

#endif //PORTAL_CONSTANTS_H
