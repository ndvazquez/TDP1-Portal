//
// Created by ndv on 5/28/19.
//

#ifndef PORTAL_CONSTANTS_H
#define PORTAL_CONSTANTS_H

enum State {
    IDLE,
    JUMPING,
    DEAD,
    MOVING_LEFT,
    MOVING_RIGHT
};

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

// AudioSystem sound codes.
#define RUN_SOUND 0
#define JUMP_SOUND 1

#endif //PORTAL_CONSTANTS_H
