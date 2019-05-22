//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "StaticObject.h"
#include "AnimatedObject.h"

class Chell : public AnimatedObject {
public:
    Chell(const std::string &path, Window &window, int totalFrames);
    ~Chell();
    void draw(SDL_Rect* rect) override;
    bool canBeOn() override;

    bool canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string> &names) override;
};


#endif //PORTAL_CHELL_H
