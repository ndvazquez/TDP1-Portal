//
// Created by ndv on 6/20/19.
//

#include "RoomWorker.h"
#include <iostream>

RoomWorker::RoomWorker(Socket &socket, RoomManager &roomManager) :
         roomManager(roomManager),
         clientSocket(std::move(socket)),
         clientProtocol(clientSocket) {
}

RoomWorker::~RoomWorker() {
}

void RoomWorker::stop() {
    clientSocket.shutdownAndClose();
}

void RoomWorker::run() {
    while (!_isDead){
        try {
            // Remove finished games
            roomManager.removeFinishedGames();
            // Prepare message with available games.
            std::vector<std::string> availableGames = roomManager.getAvailableGames();
            nlohmann::json availableGamesJson;
            availableGamesJson["games"] = availableGames;

            // Send the games availables to the client.
            std::string gamesString = availableGamesJson.dump();
            clientProtocol.sendMessage(gamesString);

            // Receive what the client wants to do.
           std::string clientAction = clientProtocol.receiveMessage();
            nlohmann::json clientActionJson = nlohmann::json::parse(clientAction);
            int action = clientActionJson["action"].get<int>();
            if (action == CREATE_GAME_CODE) {
                // Prepare message with available levels.
                std::vector<std::string> availableLevels = roomManager.getAvailableLevels();
                nlohmann::json availableLevelsJson;
                availableLevelsJson["levels"] = availableLevels;

                // Send the available levels to the client.
                std::string levelString = availableLevelsJson.dump();
                clientProtocol.sendMessage(levelString);
            }
            // Receive the other fields from the client.
            std::string clientFields = clientProtocol.receiveMessage();
            nlohmann::json clientFieldJson = nlohmann::json::parse(clientFields);
            if (action == CREATE_GAME_CODE) {
                // Receive the path of the level
                std::string levelPath = clientProtocol.receiveMessage();
                _isDead = (handleGameCreation(clientFieldJson, levelPath) &&
                        handleJoinGame(clientFieldJson));
            } else if (action == JOIN_GAME_CODE) {
                _isDead = handleJoinGame(clientFieldJson);
            }
            if (!_isDead) {
                // If something went wrong, we send a message to the client
                // to let them know, and we start from the top.
                nlohmann::json failJson;
                failJson["result"] = FAIL_CODE;
                failJson["desc"] = "Couldn't join or create the game.";
                std::string failJsonString = failJson.dump();
                clientProtocol.sendMessage(failJsonString);
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            // Client disconnected or the socket failed at some point.
            _isDead = true;
        } catch(...) {
            std::cout << "Unexpected error\n";
            // Any other error.
            _isDead = true;
        }
    }
}

bool RoomWorker::handleGameCreation(nlohmann::json& actionData, std::string& levelPath) {
    std::string gameName = actionData["gameName"].get<std::string>();
    bool result = roomManager.createGame(gameName, levelPath);
    return result;
}

bool RoomWorker::handleJoinGame(nlohmann::json& actionData) {
    std::string gameName = actionData["gameName"].get<std::string>();
    std::string playerId = actionData["id"].get<std::string>();
    bool result = roomManager.addPlayerToGame(clientSocket, gameName, playerId);
    return result;
}
