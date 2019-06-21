//
// Created by camix on 20/06/19.
//

#ifndef PORTAL_OUTPUTTEXT_H
#define PORTAL_OUTPUTTEXT_H


/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Window.h"

const SDL_Color GREEN_MOLD = {124, 120, 33};
const SDL_Color WHITE = {225, 225, 225};
const SDL_Color BLACK = {0,0,0};
const SDL_Color LIGHT_GRAY {211, 211, 211};
const SDL_Color SILVER {192,192,192};
const SDL_Color DARK_GRAY {169,169,169};
const SDL_Color GRAY {128,128,128};

//Texture wrapper class
class OutputText {
private:
    //The actual hardware texture
    SDL_Texture* mTexture{};
    TTF_Font* font;

    //Image dimensions
    int mWidth{};
    int mHeight{};
    Window& window;
    SDL_Color color;


public:
    //Initializes variables
    OutputText(Window &window, const char *message, SDL_Color color = WHITE);

    //Deallocates memory
    ~OutputText();


    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    int getWidth();
    int getHeight();


    void draw(int x, int y);

    void draw(SDL_Rect *destRect);

    void drawInTheCenter();

    void drawFromTheCenter(signed x, signed y);

    void changeMessage(const char *message);

    void writeTheScreen(std::string &message);
};

class TextException: public std::exception {
    const char* error;
public:
    TextException(const char* error) :
            error(error){}
    virtual const char* what() const throw() {
        std::string message = "There was an error initializing the text: ";
        message += error;
        return message.c_str();
    }
};

class TextInitException: public TextException {
public:
    TextInitException(const char* error) :
            TextException(error){}
};

class TextChangeNameException: public TextException {
public:
    TextChangeNameException(const char* error) :
            TextException(error){}
};

#endif //PORTAL_OUTPUTTEXT_H
