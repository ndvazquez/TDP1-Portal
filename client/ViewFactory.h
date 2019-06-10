//
// Created by ndv on 6/9/19.
//

#ifndef PORTAL_VIEWFACTORY_H
#define PORTAL_VIEWFACTORY_H


#include "../common/Window.h"
#include <yaml-cpp/yaml.h>
#include "SoundCodeQueue.h"
#include "View.h"
#include "../common/constants.h"

#define TEXTURES_DATA_PATH "config/textures.yaml"

class ViewFactory {
    int mtpFactor;
    YAML::Node texturesData;
public:
    ViewFactory(int mtpFactor);
    ~ViewFactory();
    View* createView(int viewTypeCode,
            Window& gameWindow,
            SoundCodeQueue& soundCodeQueue);
};


#endif //PORTAL_VIEWFACTORY_H
