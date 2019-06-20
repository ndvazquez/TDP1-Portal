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
const SDL_Color BLACK = {0, 0, 0};


//Texture wrapper class
class OutputText {
private:
    //The actual hardware texture
    SDL_Texture* mTexture{};

    //Image dimensions
    int mWidth{};
    int mHeight{};
    Window& window;

public:
    //Initializes variables
    OutputText(Window &window, const char *message, SDL_Color color = BLACK);

    //Deallocates memory
    ~OutputText();


    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );


    void draw(int x, int y);

    void draw(SDL_Rect *destRect);

    void drawInTheCenter();

    void drawFromTheCenter(int x, int y);
};

class TextInitException: public std::exception {
    const char* error;
public:
    TextInitException(const char* error) :
            error(error){}
    virtual const char* what() const throw() {
        std::string message = "There was an error initializing the text: ";
        message += error;
        return message.c_str();
    }
};


#endif //PORTAL_OUTPUTTEXT_H
