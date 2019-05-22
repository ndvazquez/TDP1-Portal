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

    bool canBeOn() override;
};


#endif //PORTAL_CHELL_H
