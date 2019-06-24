//
// Created by ndv on 5/31/19.
//

#include "Camera.h"
#include "SDL.h"

Camera::Camera(int screenWidth, int screenHeight,
        int levelWidth, int levelHeight) :
        levelWidth(levelWidth),
        levelHeight(levelHeight) {
        // If the level is smaller than the camera in some way,
        // then we'll set the camera size according to the level size.
       cameraRect.w = screenWidth <= levelWidth ? screenWidth : levelWidth;
       cameraRect.h = screenHeight <= levelHeight ? screenHeight : levelHeight;
       cameraRect.x = 0;
       cameraRect.y = 0;
}

Camera::~Camera() {}

const SDL_Rect& Camera::getCameraRectangle() {
    std::unique_lock<std::mutex> _lock(_mtx);
    return cameraRect;
}

void Camera::centerCameraOnPlayer(int playerPosX, int playerPosY) {
    std::unique_lock<std::mutex> _lock(_mtx);
    cameraRect.x = playerPosX  - cameraRect.w / 2;
    cameraRect.y = playerPosY- cameraRect.h / 2;

    if (cameraRect.x < 0) {
        cameraRect.x = 0;
    }
    if (cameraRect.y < 0) {
        cameraRect.y = 0;
    }
    if (cameraRect.x > levelWidth - cameraRect.w) {
        cameraRect.x = levelWidth - cameraRect.w;
    }
    if (cameraRect.y > levelHeight - cameraRect.h) {
        cameraRect.y = levelHeight - cameraRect.h;
    }
    _cv.notify_one();
}

int Camera::getCameraX() const {
    return cameraRect.x;
}

int Camera::getCameraY() const{
    return cameraRect.y;
}
