//
// Created by ndv on 6/23/19.
//

#ifndef PORTAL_RECEPTORLEFTVIEW_H
#define PORTAL_RECEPTORLEFTVIEW_H


#include "View.h"
#include "../../common/Sprite.h"
#include <unordered_map>
#include <string>
#include <yaml-cpp/yaml.h>
#include "../../common/constants.h"

#define TEXTURES_ER_LEFT_KEY "ReceptorLeft"
#define RECEPTOR_STATE_ON 1
#define RECEPTOR_STATE_OFF 0

class ReceptorLeftView : public View{
    int receptorState;
    std::unordered_map<int, Sprite*> sprites;
public:
    ReceptorLeftView(Window& window,
                     int xPos,
                     int yPos,
                     int factor,
                     YAML::Node texturesData);
    ~ReceptorLeftView();
    void setState(int state);
    void playAnimation(const SDL_Rect& camera);
};


#endif //PORTAL_RECEPTORLEFTVIEW_H
