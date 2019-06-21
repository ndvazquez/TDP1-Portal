//
// Created by camix on 20/06/19.
//

#include <iostream>
#include <unistd.h>
#include "OutputText.h"


#define X_CENTER window.getWindowWidth()/2 - mWidth/2
#define Y_CENTER window.getWindowHeight()/2 - mHeight/2
#define DEFAULT_FONT "font.ttf"
#define STEP 180
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* G_RENDER = NULL;

//Globally used font
TTF_Font *G_FONT = NULL;

OutputText::OutputText(Window &window, const char *message, SDL_Color color) :
        window(window), color(color){
    //Render text surface
    font = TTF_OpenFont(DEFAULT_FONT, 28);
    //If there was an error in loading the font
    if (font == NULL) {
        throw TextInitException(TTF_GetError());
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, this->color);

    if (!textSurface) {
        throw TextInitException(TTF_GetError());
    }

    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
    if (!mTexture) {
        throw TextInitException(SDL_GetError());
    }
    //Get image dimensions
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
}

OutputText::~OutputText() {
    if (mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void OutputText::changeMessage(const char *message) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);

    if (!textSurface) {
        throw TextChangeNameException(TTF_GetError());
    }

    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
    if (!mTexture) {
        throw TextChangeNameException(SDL_GetError());
    }
    //Get image dimensions
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
}



void OutputText::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void OutputText::setBlendMode( SDL_BlendMode blending ) {
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void OutputText::setAlpha( Uint8 alpha ) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}


void OutputText::draw(int x, int y) {
    SDL_Rect sourceRect = {0, 0 ,this->mWidth ,this->mHeight};
    SDL_Rect destRect = {x, y, this->mWidth, this->mHeight};

    window.draw(*this->mTexture, sourceRect, destRect);
}

void OutputText::draw(SDL_Rect* destRect) {
    SDL_Rect sourceRect;
    sourceRect = {0, 0, this->mWidth ,this->mHeight};
    destRect->w = mWidth;
    destRect->h = mHeight;
    window.draw(*this->mTexture, sourceRect, *destRect);
}

void OutputText::drawInTheCenter() {
    drawFromTheCenter(0,0);
}

void OutputText::drawFromTheCenter(signed x, signed y) {
    SDL_Rect sourceRect = {0, 0 ,this->mWidth ,this->mHeight};
    SDL_Rect destRect;
    destRect = {X_CENTER - x , Y_CENTER - y, this->mWidth, this->mHeight};
    window.draw(*this->mTexture, sourceRect, destRect);
}

int OutputText::getWidth() {
    return mWidth;
}

int OutputText::getHeight() {
    return mHeight;
}

void OutputText::writeTheScreen(std::string &message) {
    message += " ";
    std::string aux;
    for(size_t i = 1; i < message.size(); i++) {
        window.clear();
        window.drawBlackBackground();
        aux = message.substr(0,i);
        changeMessage(aux.c_str());
        drawInTheCenter();
        window.render();
        SDL_Delay(STEP);
    }
}