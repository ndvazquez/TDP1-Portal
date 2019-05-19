//
// Created by ndv on 5/5/19.
//
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "../common/AnimatedSprite.h"
#include "../common/StageView.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "../common/SDLSession.h"
#include "ChellView.h"
#include <yaml-cpp/yaml.h>
#include <Stage.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 1500
#define LEVEL_HEIGHT 1500
#define MATRIX_TO_PIXEL_FACTOR 100
#define METER_TO_PIXEL 100
#define CHELL_HEIGHT 210
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void drawChellWithBox2D(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    std::string bgPath = "resources/Backgrounds/Industrial.png";
    Sprite background(bgPath, newWindow);

    StageView stageView(newWindow, textures, MATRIX_TO_PIXEL_FACTOR);
    // We'll setup a very basic map, 15x15 blocks.
    std::string metalBlock = "MetalBlock";
    std::string rockBlock = "RockBlock";
    for (int i = 0; i < 15; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 14, metalBlock);
    }
    for (int i = 0; i < 15; ++i){
        stageView.addTile(0, i, rockBlock);
        stageView.addTile(14, i, rockBlock);
    }

    // Box2D Stuff.
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 2;
    // We'll subtract 1 block from the world stage for now because it will make Chell collide
    // with the borders of what's being rendered on screen.
    Stage stage(14, 14); // 1m == 1 block == 100px
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);

    int chellInitPosX = xPos * METER_TO_PIXEL;
    // Inverted y axis.
    int chellInitPosY = yPos * METER_TO_PIXEL * -1 + LEVEL_HEIGHT - CHELL_HEIGHT;

    ChellView chellView(newWindow, chellInitPosX, chellInitPosY, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {chellInitPosX, chellInitPosY, SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            chellView.handleEvent(e, keys);
            // This should be done server side, but we'll do the event handling here for now.
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }
        stage.step(chell);
        std::cout << "Chell X: " << chell->getHorizontalPosition() << std::endl;
        int newPosX = chell->getHorizontalPosition() * METER_TO_PIXEL;
        int newPosY = chell->getVerticalPosition() * METER_TO_PIXEL * -1 + LEVEL_HEIGHT - CHELL_HEIGHT;
        // We move the animated sprite for Chell.
        chellView.move(newPosX, newPosY);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);
        newWindow.clear();
        background.draw(newWindow, nullptr);
        stageView.draw(newWindow, &camera);
        chellView.playAnimation(camera);
        newWindow.render();
    }
    delete coordinate;
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);

    drawChellWithBox2D();
}
