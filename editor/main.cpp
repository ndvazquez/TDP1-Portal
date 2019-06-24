//
// Created by camix on 13/05/19.
//

#include <fstream>
#include "Editor.h"
#include "Event.h"
#include "../common/InputText.h"
#include "HomeScreen.h"
#include "stage/InputManager.h"

#define TOTAL_WIDTH  1500
#define TOTAL_HEIGHT 1000
#define TEXTURE_CONFIG_FILE "config/textures.yaml"


int main(int argc, char* argv[]) {
    try {
        SDLSession sdlSession(SDL_INIT_VIDEO);
        Window window("EDITOR", TOTAL_WIDTH, TOTAL_HEIGHT, SDL_WINDOW_SHOWN);

        HomeScreen home(window);
        std::string& yamlPath = home.start(true);

        Editor editor(window, yamlPath);
        editor.draw(0, 0);

        
        bool quit;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened

                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN: // if the event is mouse click
                        //if (e.button.button = SDL_BUTTON_RIGHT) { // and its a left click
                        //    break;
                        //}
                        if (e.button.clicks == 2 &&
                            e.button.button == SDL_BUTTON_LEFT) {
                            editor.handleMouseDoubleClick(&e);
                        } else if (e.button.clicks == 1 &&
                                   e.button.button == SDL_BUTTON_LEFT) {
                            editor.handleMouseButtonDown(&e);
                        } else if (e.button.button == SDL_BUTTON_RIGHT) {
                            editor.handleMouseRightClick(&e);
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (e.button.clicks == 1 &&
                            e.button.button == SDL_BUTTON_LEFT) {
                            editor.handleMouseButtonUp(&e);
                        }
                        break;
                    case SDL_KEYDOWN:
                        if (e.key.keysym.sym == SDLK_RIGHT && e.key.repeat == 0) {
                            editor.handleRight();
                        } else if (e.key.keysym.sym == SDLK_LEFT &&
                                   e.key.repeat == 0) {
                            editor.handleLeft();
                        } else if (e.key.keysym.sym == SDLK_UP &&
                                   e.key.repeat == 0) {
                            editor.handleUp();
                        } else if (e.key.keysym.sym == SDLK_DOWN &&
                            e.key.repeat == 0) {
                            editor.handleDown();
                        } else if (e.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL) {
                            std::string& yamlPath = home.start();
                            editor.save(yamlPath);
                        }
                }
            }
            editor.draw((int) e.motion.x, (int) e.motion.y);
        }

        SDL_Delay(500);
    }
    catch (CloseException &e ) {
        return 0;
    }
    catch (CloseInputManagerException& e) {

    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}