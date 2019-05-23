//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H


#include "StaticObject.h"

class Gate : public StaticObject {
public:
    Gate(std::string& path, Window& window);
    ~Gate();
    void draw(SDL_Rect* rect) override;
    bool canBeOn() override;

    bool canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string> &names) override;
    void setName() override;
};


#endif //PORTAL_GATE_H
