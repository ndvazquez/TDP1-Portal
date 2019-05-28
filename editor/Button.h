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
    Button(std::string& path, Window& window, const std::string& name, int w, int h);
    ~Button();

    void setName() override;
};


#endif //PORTAL_BUTTON_H
