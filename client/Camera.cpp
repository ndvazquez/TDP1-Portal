//
// Created by ndv on 5/31/19.
//

#include "Camera.h"
#include "SDL.h"

Camera::Camera(int screenWidth, int screenHeight,
        int levelWidth, int levelHeight) :
        levelWidth(levelWidth),
        levelHeight(levelHeight) {
       cameraRect.w = screenWidth;
       cameraRect.h = screenHeight;
       cameraRect.x = 0;
       cameraRect.y = 0;
}

Camera::~Camera() {}

const SDL_Rect& Camera::getCameraRectangle() {
    return cameraRect;
}

void Camera::centerCameraOnPlayer(int playerPosX, int playerPosY) {
    cameraRect.x = playerPosX  - cameraRect.w / 2;
    cameraRect.y = playerPosY- cameraRect.h / 2;

    if(cameraRect.x < 0){
        cameraRect.x = 0;
    }
    if(cameraRect.y < 0){
        cameraRect.y = 0;
    }
    if(cameraRect.x > levelWidth - cameraRect.w){
        cameraRect.x = levelWidth - cameraRect.w;
    }
    if(cameraRect.y > levelHeight - cameraRect.h){
        cameraRect.y = levelHeight - cameraRect.h;
    }
}