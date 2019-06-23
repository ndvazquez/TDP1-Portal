//
// Created by ndv on 6/12/19.
//

#include "UserEventHandler.h"
#include <SDL.h>
#include <iostream>

UserEventHandler::UserEventHandler(const Camera &camera,
        UserEventQueue &userEventQueue,
        const std::string& userId,
        int levelHeight, SoundCodeQueue& soundCodeQueue) :
        camera(camera),
        userEventQueue(userEventQueue),
        userId(userId),
        levelHeight(levelHeight),
        soundCodeQueue(soundCodeQueue){
}

UserEventHandler::~UserEventHandler() {}

void UserEventHandler::run() {
    SDL_Event event;
    while (SDL_WaitEvent(&event) != 0){
        handleEvent(event);
        if (_isDead) break;
    }
}

void UserEventHandler::stop() {
    _isDead = true;
}

void UserEventHandler::handleEvent(SDL_Event &event) {
    float xMeters = 0;
    float yMeters = 0;
    UserEvent userEvent;
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch (event.type) {
        case SDL_QUIT:
            userEvent = UserEvent(userId, USER_QUIT_CODE, xMeters, yMeters);
            userEventQueue.push(userEvent);
            _isDead = true;
            break;
        case SDL_KEYDOWN:
            int eventCode;
            if (event.key.keysym.sym == SDLK_w && event.key.repeat == 0) {
                eventCode = USER_JUMP_CODE;
            } else if (event.key.keysym.sym == SDLK_d && event.key.repeat == 0) {
                eventCode = USER_MOVE_RIGHT_CODE;
            } else if (event.key.keysym.sym == SDLK_a && event.key.repeat == 0) {
                eventCode = USER_MOVE_LEFT_CODE;
            } else if (event.key.keysym.sym == SDLK_g && event.key.repeat == 0) {
                eventCode = USER_GRAB_ROCK;
            } else if (event.key.keysym.sym == SDLK_f && event.key.repeat == 0) {
                eventCode = USER_DROP_ROCK;
            }
            else if (event.key.keysym.sym == SDLK_t && event.key.repeat == 0) {
                eventCode = USER_THROW_ROCK;
            }
            else if (event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
                eventCode = USER_REMOVE_PORTAL;
            }

            else {
                break;
            }
            userEvent = UserEvent(userId, eventCode, xMeters, yMeters);
            userEventQueue.push(userEvent);
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w ||
                event.key.keysym.sym == SDLK_d ||
                event.key.keysym.sym == SDLK_a) {
                userEvent = UserEvent(userId, USER_STOP_CODE,
                                      xMeters, yMeters);
                userEventQueue.push(userEvent);
            }
        case SDL_MOUSEBUTTONDOWN:
            xMeters = (x + camera.getCameraX()) * mtpFactorInv;
            yMeters = ((y + camera.getCameraY()) * -1 +
                       levelHeight) *mtpFactorInv;
            if (event.button.button == SDL_BUTTON_LEFT) {
                soundCodeQueue.push(PORTAL_GUN_SOUND);
                userEvent = UserEvent(userId, USER_BLUE_PORTAL_CODE,
                                      xMeters, yMeters);
                userEventQueue.push(userEvent);
                break;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                soundCodeQueue.push(PORTAL_GUN_SOUND);
                userEvent = UserEvent(userId, USER_ORANGE_PORTAL_CODE,
                                      xMeters, yMeters);
                userEventQueue.push(userEvent);
                break;
            }
        default:
            break;
    }
}