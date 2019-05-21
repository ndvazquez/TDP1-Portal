//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_MOUSEBUTTONDOWN_H
#define PORTAL_MOUSEBUTTONDOWN_H

#include <SDL_types.h>
#include "Event.h"

class MouseButtonDown : public Event {
private:
    Sint32 x;
    Sint32 y;

public:
    MouseButtonDown(Sint32 x, Sint32 y);
    Sint32 getX();
    Sint32 getY();
};


#endif //PORTAL_MOUSEBUTTONDOWN_H
