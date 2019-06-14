//
// Created by ndv on 5/27/19.
//

#ifndef PORTAL_BUTTONVIEW_H
#define PORTAL_BUTTONVIEW_H

#include "View.h"
#include "../common/Sprite.h"
#include <unordered_map>
#include <string>
#include <yaml-cpp/yaml.h>
#include "../common/constants.h"

#define TEXTURES_BUTTON_KEY "Button"
#define BUTTON_STATE_ON 0
#define BUTTON_STATE_OFF 1

class ButtonView : public View{
    int buttonState;
    std::unordered_map<int, Sprite*> sprites;
public:
    ButtonView(Window& window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node texturesData);
    ~ButtonView();
    void setState(int state);
    void playAnimation(const SDL_Rect& camera);
};


#endif //PORTAL_BUTTONVIEW_H
