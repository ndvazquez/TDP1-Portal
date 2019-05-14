//
// Created by camix on 13/05/19.
//

#include "../common/SDLSession.h"
#include "../common/Window.h"
#include "Matrix.h"
#include "BrickBlockImage.h"
#include "BrickBlockImageContainer.h"
#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>


#define BLOCK_WIDTH 80
#define BLOCK_HEIGHT 80
#define BLOCKS_AMOUNT_SCREEN_WIDTH 20
#define BLOCKS_AMOUNT_SCREEN_HEIGHT 10
#define SCREEN_WIDTH (BLOCK_WIDTH) * (BLOCKS_AMOUNT_SCREEN_WIDTH)
#define SCREEN_HEIGHT (BLOCK_HEIGHT) * (BLOCKS_AMOUNT_SCREEN_HEIGHT)



int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);
    Menu menu;

    /* window division with rectangles:
     **************************************************************************
     *        *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
     *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *        *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
     *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *        *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
     *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *        *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
     **************************************************************************
     */
    Matrix matrix(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);
    std::string title = "Editor";
    Window window(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);


    BrickBlockImageContainer brickBlocks;
    //SDL_Rect *rect = matrix.getRectangle(0,0);
    //brickBlocks.insert(rect);

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }

            window.clear();
            menu.draw(window);
            brickBlocks.draw(window);
            window.render();
        }
    }

    SDL_Delay(500);
}