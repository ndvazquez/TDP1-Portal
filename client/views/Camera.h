//
// Created by ndv on 5/31/19.
//

#ifndef PORTAL_CAMERA_H
#define PORTAL_CAMERA_H
#include <SDL.h>
#include <mutex>
#include <condition_variable>

class Camera {
    int levelWidth;
    int levelHeight;
    SDL_Rect cameraRect;
    std::condition_variable _cv;
    std::mutex _mtx;
public:
    Camera(int screenWidth, int screenHeight, int levelWidth, int levelHeight);
    ~Camera();
    const SDL_Rect& getCameraRectangle();
    // Receives the player position, centered on the player's mass center.
    void centerCameraOnPlayer(int playerPosX, int playerPosY);
    int getCameraX() const;
    int getCameraY() const;
};


#endif //PORTAL_CAMERA_H
