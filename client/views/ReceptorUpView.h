//
// Created by ndv on 6/23/19.
//

#ifndef PORTAL_RECEPTORUPVIEW_H
#define PORTAL_RECEPTORUPVIEW_H

#include "View.h"
#include "../../common/Sprite.h"
#include <unordered_map>
#include <string>
#include <yaml-cpp/yaml.h>
#include "../../common/constants.h"

#define TEXTURES_ER_UP_KEY "ReceptorUp"
#define RECEPTOR_STATE_ON 1
#define RECEPTOR_STATE_OFF 0

class ReceptorUpView : public View{
    int receptorState;
    std::unordered_map<int, Sprite*> sprites;
public:
    ReceptorUpView(Window& window,
               int xPos,
               int yPos,
               int factor,
               YAML::Node& texturesData);
    ~ReceptorUpView();
    void setState(int state);
    void playAnimation(const SDL_Rect& camera);
};


#endif //PORTAL_RECEPTORUPVIEW_H
