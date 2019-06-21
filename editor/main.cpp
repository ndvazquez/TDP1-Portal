//
// Created by camix on 13/05/19.
//

#include <fstream>
#include "Editor.h"
#include "Event.h"
#include "../common/InputText.h"

#define TOTAL_WIDTH  1500
#define TOTAL_HEIGHT 1000
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

#define SET_YAML_MESSAGE "SI USTED REALMENTE DESEA EL PASTEL INGRESE EL NOMBRE DE UN ARCHIVO YAML DEL CUAL LEER EL ESCENARIO"
#define NO_YAML "SALTEAR (NO SOY MERECEDOR DEL PASTEL)"


#define ENTERING_DONE "OK, ACÁ ESTÁ EL ARCHIVO. YA PUEDO TENER MI PASTEL?"

int main(int argc, char* argv[]) {
    try {
        SDLSession sdlSession(SDL_INIT_VIDEO);
        Window window("EDITOR", TOTAL_WIDTH, TOTAL_HEIGHT, SDL_WINDOW_SHOWN);

        InputText input(window, SET_YAML_MESSAGE, GREEN_MOLD);
        SDL_Event e;
        bool quit = false;
        int width = window.getWindowWidth();
        int height = window.getWindowHeight();
        SDL_Rect noYaml = {0,10,50,50};
        OutputText noYamlImage(window, NO_YAML, BLACK);
        SDL_Rect done = {0,height - 100,50,50};
        OutputText doneImage(window, ENTERING_DONE, BLACK);
        const char* droppedFilePath;
        std::string& yamlPath = input.getText();
        bool quitInitialMenu = false;
        while (!quitInitialMenu) {
            while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened
                if (e.type == SDL_MOUSEBUTTONDOWN &&
                    e.button.clicks == 1 &&
                    e.button.button == SDL_BUTTON_LEFT) {
                    SDL_Point sdlPoint = {e.button.x, e.button.y};
                    if ((bool) SDL_PointInRect(&sdlPoint, &noYaml)) {
                        std::cerr << "sali en el boton SIN archivo" << std::endl;
                        yamlPath = "";

                        quitInitialMenu = true;
                        break;
                    }
                    if ((bool) SDL_PointInRect(&sdlPoint, &done)) {

                        std::cerr << "sali en el boton CON archivo" << std::endl;
                        std::cerr << "\tel archivo era: " << yamlPath << std::endl;
                        quitInitialMenu = true;
                        break;
                    }
                }
                if (e.type == SDL_QUIT) {
                    quitInitialMenu = true;
                    quit = true;
                    break;
                }
                if (e.type == SDL_DROPFILE) {
                    yamlPath = e.drop.file;
                    quitInitialMenu = true;
                    break;
                }
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_ENTER) {
                    quitInitialMenu = true;
                    break;
                } else {
                    input.handle(&e);
                    window.clear();
                    noYamlImage.draw(&noYaml);
                    doneImage.draw(&done);
                    input.drawFromTheCenter(0, 0);
                    window.render();
                    //std::cerr << "Dibuje devuelta" << std::endl;
                }
                //std::cerr << "Dibuje devuelta" << std::endl;
            }
        }


        if (quit) return 0;
        Editor editor(window, yamlPath);
        editor.draw(0, 0);


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
                        } else if (e.key.keysym.sym == SDLK_s &&
                                   e.key.repeat == 0) {
                            editor.save();
                        }
                }
            }
            editor.draw((int) e.motion.x, (int) e.motion.y);
        }

        SDL_Delay(500);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}