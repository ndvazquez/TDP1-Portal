//
// Created by ndv on 6/9/19.
//

#include "ViewFactory.h"
#include "ChellView.h"
#include "AcidView.h"
#include "EnergyBallView.h"
#include "PortalView.h"
#include "RockView.h"
#include "ButtonView.h"
#include "BulletView.h"
#include "CakeView.h"

ViewFactory::ViewFactory(int mtpFactor) :
        mtpFactor(mtpFactor) {
    texturesData = YAML::LoadFile(TEXTURES_DATA_PATH);
}

ViewFactory::~ViewFactory() {}

View* ViewFactory::createView(int viewTypeCode,
        Window &gameWindow,
        SoundCodeQueue &soundCodeQueue) {
    View* newView = nullptr;
    switch (viewTypeCode) {
        case CHELL_VIEW_CODE:
            newView = new ChellView(gameWindow,0, 0,
                    mtpFactor, soundCodeQueue, texturesData);
            break;
        case ACID_VIEW_CODE:
            newView = new AcidView(gameWindow, 0, 0, mtpFactor, texturesData);
            break;
        case ENERGY_BALL__VIEW_CODE:
            newView = new EnergyBallView(gameWindow, 0, 0, mtpFactor,
                    texturesData);
            break;
        case ROCK_VIEW_CODE:
            newView = new RockView(gameWindow, 0, 0, mtpFactor, texturesData);
            break;
        case PORTAL_VIEW_CODE:
            newView = new PortalView(gameWindow, 0, 0, mtpFactor,
                    texturesData);
            break;
        case BUTTON_VIEW_CODE:
            newView = new ButtonView(gameWindow, 0, 0, mtpFactor,
                    texturesData);
            break;
        case BULLET_VIEW_CODE:
            newView = new BulletView(gameWindow, 0, 0, mtpFactor,
                    texturesData);
            break;
        case CAKE_VIEW_CODE:
            newView = new CakeView(gameWindow, 0, 0, mtpFactor,
                    texturesData);
        default:
            break;
    }
    return newView;
}
