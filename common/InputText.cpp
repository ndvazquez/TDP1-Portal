//
// Created by camix on 20/06/19.
//

#include <iostream>
#include "InputText.h"


#define INITIAL ">>  "

//Handle backspace
void InputText::handle(SDL_Event* e) {
    if( e->type == SDL_KEYDOWN ) {
        if( e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
            //lop off character
            inputText.pop_back();
            renderText = true;
        } else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
            //Handle copy
            SDL_SetClipboardText( inputText.c_str() );
        } else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
            //Handle paste
            inputText = SDL_GetClipboardText();
            renderText = true;
        }
    }
    if( e->type == SDL_TEXTINPUT && //Special text input event
                //Not copy or pasting
            !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) &&
            ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) &&
            SDL_GetModState() & KMOD_CTRL ) ) {
        inputText += e->text.text;

        renderText = true;
    }
}

InputText::InputText(Window &window, const char *message, SDL_Color color = WHITE) :
    outputImage(window, message, color),
    initial(INITIAL),
    inputText(),
    inputImage(window, INITIAL, SILVER),
    renderText(false),
    space(std::round(4.0 * outputImage.getHeight()/3)) {
}

InputText::~InputText() = default;

void InputText::draw(int x, int y) {
    refreshOutput();
    outputImage.draw(x, y);
    inputImage.draw(x,y + space);
}


void InputText::draw(SDL_Rect *destRect) {
    refreshOutput();
    outputImage.draw(destRect);
    SDL_Rect newRect = {destRect->x, destRect->y, destRect->w, destRect->h};
    newRect.y += space;
    inputImage.draw(&newRect);
}

void InputText::drawInTheCenter() {
    refreshOutput();
    outputImage.drawFromTheCenter(0, 0-space/2);
    inputImage.drawFromTheCenter(0, space/2);
}

void InputText::drawFromTheCenter(signed x, signed y) {
    refreshOutput();
    outputImage.drawFromTheCenter(x, y-space/2);
    inputImage.drawFromTheCenter(x, y+space/2);
}

void InputText::refreshOutput() {
    if(!renderText) return;
    inputImage.changeMessage((initial +inputText).c_str());
    renderText = false;
}

std::string &InputText::getText() {
    return inputText;
}
