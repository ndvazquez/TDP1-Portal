//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H


#include <string>
#include <map>
#include "../../../common/Window.h"
#include "StaticObject.h"

class Button : public StaticObject {
private:
    std::map<std::pair<int, int>, std::string> names;

public:
    Button(std::string& path, Window& window, const std::string& name, int w, int h);
    ~Button();

    void setName(std::pair<int, int> position, std::string& enteredName) override;
    bool doesThisNameExist(std::string &string) override;
};


#endif //PORTAL_BUTTON_H
