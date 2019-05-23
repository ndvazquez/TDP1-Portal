//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_MOUSEBUTTON_H
#define PORTAL_MOUSEBUTTON_H


#include <SDL_types.h>
#include <SDL_events.h>

class MouseButton {
private:
    SDL_Event* event;

public:
    explicit MouseButton(SDL_Event* event);
    Sint32 getX();
    Sint32 getY();
};


#endif //PORTAL_MOUSEBUTTON_H
