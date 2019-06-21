//
// Created by ndv on 6/19/19.
//

#include "RoomManager.h"
#include <iostream>

RoomManager::RoomManager() {}

RoomManager::~RoomManager() {
//    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
//        delete it->second;
//    }
}

bool RoomManager::createGame(const std::string &gameName) {
    std::unique_lock<std::mutex> _lock(_mtx);
    if (rooms.count(gameName) > 0) {
        // There's already a game created with this name.
        return false;
    }
    float stageWidth = 17;
    float stageHeight = 18;
    StageManager* newStageManager = new StageManager(stageWidth, stageHeight);
    rooms.insert({gameName, newStageManager});
    return true;
}

bool RoomManager::addPlayerToGame(Socket &playerSocket,
        const std::string &gameName,
        const std::string &playerId) {
    std::unique_lock<std::mutex> _lock(_mtx);
    if (rooms.count(gameName) == 0) {
        // There's no game created for this gameName.
        return false;
    }
    auto it = rooms.find(gameName);
    StageManager* stageManager = it->second;
    if (stageManager->isFull()) {
        // Game is full and hence has started.
        // Can't add players!
        return false;
    }
    bool playerAddedToGame = stageManager->addPlayer(playerSocket, playerId);
    if (!playerAddedToGame) return false;
    // Start the game if it's full!
    if (stageManager->isFull()) {
        stageManager->start();
    }
    return true;
}

std::vector<std::string> RoomManager::getAvailableGames() {
    std::unique_lock<std::mutex> _lock(_mtx);
    int roomsSize = rooms.size();
    std::vector<std::string> availableGames(roomsSize);
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (!it->second->isFull()) {
            availableGames.push_back(it->first);
        }
    }
    return availableGames;
}
