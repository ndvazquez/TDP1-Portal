//
// Created by camix on 20/06/19.
//

#ifndef PORTAL_INPUTTEXT_H
#define PORTAL_INPUTTEXT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "OutputText.h"

#define READ_INPUT_ON true
#define READ_INPUT_OFF false


class InputText {
private:
    std::string initial;
    std::string inputText;
    bool renderText;
    OutputText outputImage;
    OutputText inputImage;
    int space;

public:
    InputText(Window &window, const char *message, SDL_Color color);
    ~InputText();
    void handle(SDL_Event* e);

    void draw(int x, int y);

    void draw(SDL_Rect *destRect);

    void drawInTheCenter();

    void drawFromTheCenter(signed x, signed y);

    void refreshOutput();

    std::string &getText();

    void resetText();

    std::string copyText();
};


#endif //PORTAL_INPUTTEXT_H
