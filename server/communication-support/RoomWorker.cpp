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
            // Prepare message with available games.
            std::vector<std::string> availableGames = roomManager.getAvailableGames();
            nlohmann::json availableGamesJson;
            availableGamesJson["games"] = availableGames;

            // Send the games availables to the client.
            std::string gamesString = availableGamesJson.dump();
            clientProtocol.sendMessage(gamesString);

            // Receive what the client wants to do.
           std::string clientAction = clientProtocol.receiveMessage();

            // Need to check if it's a valid JSON.
            nlohmann::json clientActionJson = nlohmann::json::parse(clientAction);
            int action = clientActionJson["action"].get<int>();
            if (action == CREATE_GAME_CODE) {
                std::string levelPath = clientProtocol.receiveMessage();
                _isDead = (handleGameCreation(clientActionJson, levelPath) &&
                        handleJoinGame(clientActionJson));
            } else if (action == JOIN_GAME_CODE) {
                _isDead = handleJoinGame(clientActionJson);
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
            std::cout << "Excepcion inesperada\n";
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
