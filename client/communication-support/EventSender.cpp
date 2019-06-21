//
// Created by ndv on 6/17/19.
//

#include "EventSender.h"

EventSender::EventSender(Socket &socket, UserEventQueue &eventQueue) :
                        clientProtocol(socket),
                        userEventQueue(eventQueue){
}

EventSender::~EventSender() {}

void EventSender::run() {
    while (!_isDead) {
        try {
            UserEvent userEvent = userEventQueue.pop();
            // No need for suicide pill, the Quit event is enough.
            if (userEvent.getEventType() == USER_QUIT_CODE){
                _isDead = true;
            }
            std::string userEventJson = userEvent.toJsonString();
            clientProtocol.sendMessage(userEventJson);
        } catch (std::runtime_error &e){
            // TODO: Implement a real exception.
            _isDead = true;
        } catch (...) {
            _isDead = true;
            return;
        }
    }
}

void EventSender::stop() {
    _isDead = true;
}
