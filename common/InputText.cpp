//
// Created by camix on 20/06/19.
//

#include <iostream>
#include "InputText.h"



//Handle backspace
void InputText::handle(SDL_Event* e) {
    std::cerr << "Estoy entrando" << std::endl;
    //if(on == READ_INPUT_ON) return;
    if( e->type == SDL_KEYDOWN ) {
        if( e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 ) {
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

        std::cerr << "Se Ingreso texto, el input actualizado es: " << inputText << std::endl;
        renderText = true;
    }
}

InputText::InputText(Window &window, const char *message, SDL_Color color = BLACK) :
    outputInstruction(window, message, color),
    inputText("Enter here: "),
    enteredText(window, inputText.c_str(), SILVER),
    renderText(false),
    on(READ_INPUT_OFF),
    space(std::round(4.0 * outputInstruction.getHeight()/3)) {
}

void InputText::startReading() {
    on = READ_INPUT_ON;
}


void InputText::stopReading() {
    on = READ_INPUT_OFF;
}

InputText::~InputText() = default;

void InputText::draw(int x, int y) {
    refreshOutput();
    outputInstruction.draw(x, y);
    enteredText.draw(x,y + space);
}


void InputText::draw(SDL_Rect *destRect) {
    refreshOutput();
    outputInstruction.draw(destRect);
    destRect->y += space;
    enteredText.draw(destRect);
}

void InputText::drawInTheCenter() {
    refreshOutput();
    outputInstruction.drawFromTheCenter(0, 0-space/2);
    enteredText.drawFromTheCenter(0, space/2);
}

void InputText::drawFromTheCenter(signed x, signed y) {
    refreshOutput();
    outputInstruction.drawFromTheCenter(x, y-space/2);
    enteredText.drawFromTheCenter(x, y+space/2);
}

void InputText::refreshOutput() {
    std::cerr << "Al dibujar el texto es: " << inputText << std::endl;
    enteredText.changeMessage(inputText.c_str());
}
