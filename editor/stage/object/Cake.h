//
// Created by camix on 28/05/19.
//

#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H

#include "AnimatedObject.h"

class Cake : public AnimatedObject {
public:
    Cake(std::string &path, Window &window, int totalFrames, const std::string& name, int w, int h);
    ~Cake();
    void draw(SDL_Rect* rect) override;
};


#endif //PORTAL_CAKE_H
