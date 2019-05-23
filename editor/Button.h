//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H


#include <string>
#include "../common/Window.h"
#include "StaticObject.h"

class Button : public StaticObject {
public:
    Button(std::string& path, Window& window);
    ~Button();

    bool canBeOn() override;
    bool canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string>& names) override;
    void setName() override;
};


#endif //PORTAL_BUTTON_H
