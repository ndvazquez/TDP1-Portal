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

int main(int argc, char* argv[]) {
    SDLSession sdlSession(SDL_INIT_VIDEO);
    Window window("EDITOR", TOTAL_WIDTH, TOTAL_HEIGHT, SDL_WINDOW_SHOWN);
/*
    std::cerr << "Antes del clear \n";
    window.clear();
    std::cerr << "Despues del clear \n";

    std::cerr << "Antes del render \n";
    window.render();
    std::cerr << "Despues del render\n";
*/
    Editor editor(window);
/*

    std::cerr << "\nDespues de crear el editor: \n";
    std::cerr << "Antes del clear \n";
    window.clear();
    std::cerr << "Despues del clear \n";

    std::cerr << "Antes del render \n";
    window.render();
    std::cerr << "Despues del render\n";

*/

    editor.draw();



    bool quit = false;
    SDL_Event e;
    Event* event;

    //std::cerr << "Antes de entrar al while(quit)\n";
    while(!quit) {

        //std::cerr << "Entre al while (quit) \n";
         while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened

             //std::cerr << "Hay un event\n";
             switch (e.type) {
                 case SDL_QUIT:

                     //std::cerr << "hola, quit \n";
                     quit = true;
                     break;
                 case SDL_MOUSEBUTTONDOWN: // if the event is mouse click
                    event = new MouseButtonDown(e.button.x, e.button.y);
                     //std::cerr << "hola, mouse \n";
                    editor.handle((MouseButtonDown*) event);
                    break;
                 case SDL_MOUSEBUTTONUP:
                     event = new MouseButtonUp(e.button.x, e.button.y);
                     editor.handle((MouseButtonUp*) event);
             }
         }

        //std::cerr << "Fuera del while sdl_event \n";
        editor.draw();
    }

    SDL_Delay(500);
}