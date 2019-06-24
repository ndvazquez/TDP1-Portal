//
// Created by ndv on 6/23/19.
//

#ifndef PORTAL_RECEPTORDOWNVIEW_H
#define PORTAL_RECEPTORDOWNVIEW_H


#include "View.h"
#include "../../common/Sprite.h"
#include <unordered_map>
#include <string>
#include <yaml-cpp/yaml.h>
#include "../../common/constants.h"

#define TEXTURES_ER_DOWN_KEY "ReceptorDown"
#define RECEPTOR_STATE_ON 1
#define RECEPTOR_STATE_OFF 0

class ReceptorDownView : public View{
    int receptorState;
    std::unordered_map<int, Sprite*> sprites;
public:
    ReceptorDownView(Window& window,
                   int xPos,
                   int yPos,
                   int factor,
                   YAML::Node texturesData);
    ~ReceptorDownView();
    void setState(int state);
    void playAnimation(const SDL_Rect& camera);
};


#endif //PORTAL_RECEPTORDOWNVIEW_H
