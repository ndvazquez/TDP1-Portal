//
// Created by camix on 13/05/19.
//

#include "Editor.h"




int main(int argc, char* argv[]) {
    SDLSession sdlSession(SDL_INIT_VIDEO);

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        /*
         while (SDL_PollEvent(&event)) { // check to see if an event has happened
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN: // if the event is mouse click
                    if(event.mouse.x >= 100)  {// check if it is in the desired area
                        //do something
                    }
            }
        }
         */
        while (SDL_PollEvent( &e ) != 0) {
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