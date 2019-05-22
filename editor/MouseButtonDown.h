//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_MOUSEBUTTONDOWN_H
#define PORTAL_MOUSEBUTTONDOWN_H

#include <SDL_types.h>
#include <SDL_events.h>
#include "Event.h"

class MouseButtonDown : public Event {
private:
    SDL_Event* event;

public:
    explicit MouseButtonDown(SDL_Event *event);
    Sint32 getX();
    Sint32 getY();
};


#endif //PORTAL_MOUSEBUTTONDOWN_H
