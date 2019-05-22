//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_MOUSEBUTTONUP_H
#define PORTAL_MOUSEBUTTONUP_H

#include <SDL_events.h>
#include "Event.h"

class MouseButtonUp : public Event{
private:
    SDL_Event* event;

public:
    explicit MouseButtonUp(SDL_Event* event);
    Sint32 getX();
    Sint32 getY();
};


#endif //PORTAL_MOUSEBUTTONUP_H
