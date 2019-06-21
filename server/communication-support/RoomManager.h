//
// Created by ndv on 6/19/19.
//

#ifndef PORTAL_ROOMMANAGER_H
#define PORTAL_ROOMMANAGER_H

#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <string>
#include <vector>
#include <stage-support/StageManager.h>

class RoomManager {
    std::mutex _mtx;
    std::unordered_map<std::string, StageManager*> rooms;
public:
    RoomManager();
    ~RoomManager();
    // Creates a game and adds the creator to the game.
    bool createGame(const std::string& gameName, std::string& levelPath);
    // First checks if the player can join the game, if it's not possible
    // the socket won't be moved to the StageManager.
    bool addPlayerToGame(Socket& playerSocket,
            const std::string& gameName,
            const std::string &playerId);
    std::vector<std::string> getAvailableGames();

};


#endif //PORTAL_ROOMMANAGER_H
