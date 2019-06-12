//
// Created by ndv on 6/12/19.
//

#ifndef PORTAL_USEREVENT_H
#define PORTAL_USEREVENT_H

#include "../json/json.hpp"
#include <string>

class UserEvent {
    std::string userId;
    int eventType;
    float userMouseX;
    float userMouseY;
public:
    UserEvent();
    explicit UserEvent(nlohmann::json& jsonData);
    UserEvent(const std::string& id,
            int eventTypeCode,
            float x,
            float y);
    ~UserEvent();
    int getEventType();
    float getUserPosX();
    float getUserPosY();
    const std::string& getUserId();
    std::string toJsonString();
};


#endif //PORTAL_USEREVENT_H
