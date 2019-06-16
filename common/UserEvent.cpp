//
// Created by ndv on 6/12/19.
//

#include "UserEvent.h"
#include <string>
#include <iostream>

UserEvent::UserEvent() {}

UserEvent::UserEvent(nlohmann::json &jsonData) {
    this->eventType = jsonData["eventType"].get<int>();
    this->userId = jsonData["id"].get<std::string>();
    this->userMouseX = jsonData["x"].get<float>();
    this->userMouseY = jsonData["y"].get<float>();
}

UserEvent::UserEvent(const std::string &id,
        int eventTypeCode, float x, float y) :
        userId(id),
        eventType(eventTypeCode),
        userMouseX(x),
        userMouseY(y) {
}

UserEvent::~UserEvent(){
}

float UserEvent::getUserPosX() {
    return this->userMouseX;
}

float UserEvent::getUserPosY() {
    return this->userMouseY;
}

const std::string& UserEvent::getUserId() {
    return this->userId;
}

int UserEvent::getEventType() {
    return this->eventType;
}

std::string UserEvent::toJsonString() {
    nlohmann::json jsonData;
    jsonData["id"] = this->userId;
    jsonData["eventType"] = this->eventType;
    jsonData["x"] = this->userMouseX;
    jsonData["y"] = this->userMouseY;
    std::string jsonString = jsonData.dump();
    return jsonString;
}
