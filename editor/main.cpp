//
// Created by camix on 13/05/19.
//

#include <fstream>
#include "Editor.h"
#include "Event.h"

#define TOTAL_WIDTH  1500
#define TOTAL_HEIGHT 1000
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

#include "MouseButtonDown.h"
#include "MouseButtonUp.h"
#include "MouseDoubleCick.h"

int main(int argc, char* argv[]) {
    SDLSession sdlSession(SDL_INIT_VIDEO);
    Window window("EDITOR", TOTAL_WIDTH, TOTAL_HEIGHT, SDL_WINDOW_SHOWN);

    Editor editor(window);
    editor.draw();

    bool quit = false;
    SDL_Event e;
    while(!quit) {
         while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened

             switch (e.type) {
                 case SDL_QUIT:
                     quit = true;
                     break;
                 case SDL_MOUSEBUTTONDOWN: // if the event is mouse click
                    if (e.button.button != SDL_BUTTON_LEFT) { // and its a left click
                        break;
                    }
                    if (e.button.clicks == 1) {
                        editor.handleMouseButtonDown(&e);
                    }
                     if (e.button.clicks == 2) {
                         editor.handleMouseDoubleCick(&e);
                     }
                    break;
                 case SDL_MOUSEBUTTONUP:
                     editor.handleMouseButtonUp(&e);
             }
         }
        editor.draw();
    }

    SDL_Delay(500);
}