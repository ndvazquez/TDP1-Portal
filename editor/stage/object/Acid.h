//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H


#include "AnimatedObject.h"

class Acid : public AnimatedObject {
public:
    Acid(std::string &path, Window &window, int totalFrames, const std::string& name, int w, int h);
    ~Acid();
    void draw(SDL_Rect* rect) override;
};


#endif //PORTAL_ACID_H
