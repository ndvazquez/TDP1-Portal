//
// Created by ndv on 6/13/19.
//

#include <iostream>
#include "StageManager.h"

StageManager::StageManager(Stage &stage,
        UserEventQueue &queue) :
        stage(stage),
        userEventQueue(queue){
    this->timeStamp = std::chrono::system_clock::now();
}

StageManager::~StageManager() {}

void StageManager::run() {
    // We're gonna run a loop here, until a player wins the game or
    // everyone loses.
    // Also, I think it's a good idea to have the time step handled
    // here, because we can consume events between steps!
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference <= 1000 / 60) {
        if (!userEventQueue.empty()){
            UserEvent userEvent = userEventQueue.pop();
            Chell* chell = stage.getChell(userEvent.getUserId());
            handleEvent(userEvent, chell);
        }
    } else {
        timeStamp = std::chrono::system_clock::now();
        stage.step();
    }
}

void StageManager::handleEvent(UserEvent &userEvent,
        Chell *chell) {
    std::string chell_id = userEvent.getUserId();
    int eventTypeCode = userEvent.getEventType();
    switch (eventTypeCode) {
        case USER_QUIT_CODE:
            // Kill Chell, I guess?
            break;
        case USER_JUMP_CODE:
            chell->jump();
            break;
        case USER_MOVE_LEFT_CODE:
            chell->moveLeft();
            break;
        case USER_MOVE_RIGHT_CODE:
            chell->moveRight();
            break;
        case USER_STOP_CODE:
            chell->stop();
            break;
        case USER_DROP_ROCK:
            chell->downloadRock();
            break;
        case USER_GRAB_ROCK:
            {
                float x_chell = chell->getHorizontalPosition();
                float y_chell = chell->getVerticalPosition();
                Rock *rock = stage.getClosestRock(x_chell, y_chell);
                chell->grabRock(rock);
            }
            break;
        case USER_BLUE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                std::cout << id << std::endl;
                id.replace(0, chell_id.length() - 1, "BlueShot");
                std::cout << id << std::endl;
                stage.addBlueShot(id, BULLET_HEIGHT, BULLET_WIDTH,
                        chell, target);
            }
            break;
        case USER_ORANGE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                id.replace(0, chell_id.length() - 1, "OrangeShot");
                stage.addOrangeShot(id, BULLET_HEIGHT, BULLET_WIDTH,
                                  chell, target);
            }
            break;
        default:
            break;
    }
}