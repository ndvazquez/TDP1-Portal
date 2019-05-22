//
// Created by camix on 21/05/19.
//

#ifndef PORTAL_MOUSEDOUBLECICK_H
#define PORTAL_MOUSEDOUBLECICK_H

#include <SDL_events.h>
#include "Event.h"

class MouseDoubleCick : public Event {
private:
    SDL_Event *event;

public:
    MouseDoubleCick(SDL_Event *event);
};


#endif //PORTAL_MOUSEDOUBLECICK_H
