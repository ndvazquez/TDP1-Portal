//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_MOUSEBUTTONUP_H
#define PORTAL_MOUSEBUTTONUP_H

#include "Event.h"

class MouseButtonUp : public Event{
private:
    Sint32 x;
    Sint32 y;

public:
    MouseButtonUp(Sint32 x, Sint32 y);
    Sint32 getX();
    Sint32 getY();
};


#endif //PORTAL_MOUSEBUTTONUP_H
