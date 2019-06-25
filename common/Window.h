//
// Created by ndv on 5/5/19.
//

#ifndef PORTAL_WINDOW_H
#define PORTAL_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <exception>
#include <mutex>

class WindowInitException: public std::exception {
    virtual const char* what() const throw() {
        std::string message = "There was an error while trying"
                              " to initialize a window: ";
        message += SDL_GetError();
        return message.c_str();
    }
};

class Window {
    friend class Sprite;
    std::mutex _mtx;
    int windowWidth;
    int windowHeight;
    bool fullScreenState;
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Window(const std::string& title, int width, int height, int flags);
    ~Window();
    //Wrapper for SDL_RenderPresent.
    void render();
    //Wrapper for SDL_RenderClear.
    void clear();
    //Wrapper for SDL_RenderCopy.
    void draw(SDL_Texture& texture,
            SDL_Rect& sourceRect,
            SDL_Rect& destRect);
    //We can flip an image horizontally or vertically with this method.
    void draw(SDL_Texture& texture,
              SDL_Rect& sourceRect,
              SDL_Rect& destRect,
              SDL_RendererFlip& flip);
    //We can rotate an image over it's center with this method.
    void draw(SDL_Texture &texture,
              SDL_Rect &sourceRect,
              SDL_Rect &destRect,
              double angle);
    void drawRectangle(SDL_Rect& outlineRect);
    int getWindowWidth();
    int getWindowHeight();
    SDL_Renderer* getRenderer();
    void drawBlackBackground();
    void drawBlackRectangle(SDL_Rect* rect);
    void changeFullScreenState();
};

#endif //PORTAL_WINDOW_H
