//
// Created by ndv on 6/19/19.
//

#include "RoomManager.h"
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <sys/types.h>
#include <dirent.h>

RoomManager::RoomManager() {}

RoomManager::~RoomManager() {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        it->second->stop();
        it->second->join();
        delete it->second;
    }
}

bool RoomManager::createGame(const std::string &gameName, std::string& levelPath) {
    std::unique_lock<std::mutex> _lock(_mtx);
    if (rooms.count(gameName) > 0) {
        // There's already a game created with this name.
        return false;
    }
    std::string actualPath = LEVELS_PATH + levelPath;
    YAML::Node metadata = YAML::LoadFile(actualPath);
    const YAML::Node& dimentions = metadata[STAGE_ATTRIBUTES][STAGE_SIZE];
    float stageWidth = dimentions[HORIZONTAL_SIZE].as<float>();
    float stageHeight = dimentions[VERTICAL_SIZE].as<float>();
    const YAML::Node& chells = metadata[std::to_string(CHELL)][OBJECT_POSITION];
    int maxPlayers = chells.size();
    StageManager* newStageManager = new StageManager(stageWidth, stageHeight, actualPath, maxPlayers);
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
    if (!playerAddedToGame) {
        return false;
    }
    // Start the game if it's full!
    if (stageManager->isFull()) {
        stageManager->start();
    }
    return true;
}

std::vector<std::string> RoomManager::getAvailableGames() {
    std::unique_lock<std::mutex> _lock(_mtx);
    std::vector<std::string> availableGames;
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (!it->second->isFull()) {
            availableGames.push_back(it->first);
        }
    }
    return availableGames;
}

std::vector<std::string> RoomManager::getAvailableLevels() {
    std::unique_lock<std::mutex> _lock(_mtx);
    std::vector<std::string> availableLevels;
    DIR* dirp = opendir(LEVELS_PATH);
    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr) {
        std::string name = dp->d_name;
        if (name.find(".yaml") == std::string::npos) continue;
        availableLevels.push_back(dp->d_name);
    }
    closedir(dirp);
    return availableLevels;
}

void RoomManager::removeFinishedGames() {
    std::unique_lock<std::mutex> _lock(_mtx);
    for (auto it = rooms.begin(); it != rooms.end();) {
        auto stageIt = it++;
        auto stage = stageIt->second;
        if (stage->isDead()) {
            stage->stop();
            stage->join();
            delete stage;
            rooms.erase(stageIt);
        }
    }
}