//
// Created by ndv on 5/5/19.
//

#ifndef PORTAL_WINDOW_H
#define PORTAL_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <exception>

class WindowInitException: public std::exception {
    virtual const char* what() const throw () {
        std::string message = "There was an error while trying to initialize a window: ";
        message += SDL_GetError();
        return message.c_str();
    }
};

class Window {
    friend class Sprite;
    int windowWidth;
    int windowHeight;
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
    int getWindowWidth();
    int getWindowHeight();
};

#endif //PORTAL_WINDOW_H
