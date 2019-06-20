//
// Created by camix on 20/06/19.
//

#include <iostream>
#include "TextOut.h"


#define X_CENTER window.getWindowWidth()/2 - mWidth/2
#define Y_CENTER window.getWindowHeight()/2 - mHeight/2
#define DEFAULT_FONT "font.ttf"
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* G_RENDER = NULL;

//Globally used font
TTF_Font *G_FONT = NULL;

TextOut::TextOut(Window &window, const char *message, SDL_Color color) :
        window(window) {
    //Render text surface
    TTF_Font* font = TTF_OpenFont(DEFAULT_FONT, 28);
    //If there was an error in loading the font
    if (font == NULL) {
        std::cerr << "Error: " << TTF_GetError() << std::endl;
        throw TextInitException(TTF_GetError());
    }

    std::cerr << "1" << std::endl;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);
    std::cerr << "2" << std::endl;

    if (!textSurface) {
        std::cerr << "Error: " << TTF_GetError() << std::endl;
        throw TextInitException(TTF_GetError());
    }

    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
    if (!mTexture) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        throw TextInitException(SDL_GetError());
    }
    //Get image dimensions
    mWidth = textSurface->w;
    std::cerr << "\tmWidth: " << mWidth << std::endl;
    mHeight = textSurface->h;

    std::cerr << "\tmHeight: " << mHeight << std::endl;
    //Get rid of old surface
    SDL_FreeSurface( textSurface );
}

TextOut::~TextOut() {
    if (mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}



void TextOut::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void TextOut::setBlendMode( SDL_BlendMode blending ) {
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void TextOut::setAlpha( Uint8 alpha ) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}


void TextOut::draw(int x, int y) {
    SDL_Rect sourceRect = {0, 0 ,this->mWidth ,this->mHeight};
    SDL_Rect destRect = {x, y, this->mWidth, this->mHeight};

    window.draw(*this->mTexture, sourceRect, destRect);
}

void TextOut::draw(SDL_Rect* destRect) {
    SDL_Rect sourceRect = {0, 0 ,this->mWidth ,this->mHeight};
    window.draw(*this->mTexture, sourceRect, *destRect);
}

void TextOut::drawInTheCenter() {
    drawFromTheCenter(0,0);
}

void TextOut::drawFromTheCenter(int x, int y) {
    SDL_Rect sourceRect = {0, 0 ,this->mWidth ,this->mHeight};
    SDL_Rect destRect = {X_CENTER - x , Y_CENTER - y, this->mWidth, this->mHeight};
    window.draw(*this->mTexture, sourceRect, destRect);
}