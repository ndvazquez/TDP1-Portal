//
// Created by ndv on 6/20/19.
//

#include "RoomWorker.h"
#include <iostream>

 RoomWorker::RoomWorker(Socket &socket, RoomManager &roomManager) :
                clientSocket(std::move(socket)),
                roomManager(roomManager) {
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
            // Extract this into a Protocol.
            // Send the games availables to the client.
            std::string gamesString = availableGamesJson.dump();
            std::cout << "Partidas disponibles: " << gamesString << std::endl;
            int gamesStringSize = gamesString.size();
            clientSocket.sendMessage(&gamesStringSize, REQUEST_LEN_SIZE);
            clientSocket.sendMessage(&gamesString[0], gamesStringSize);
            // Receive what the client wants to do.
            int clientActionSize;
            clientSocket.receiveMessage(&clientActionSize, REQUEST_LEN_SIZE);
            std::cout << "Json action size: " << clientActionSize << std::endl;
            std::string clientAction(clientActionSize, '\0');
            clientSocket.receiveMessage(&clientAction[0], clientActionSize);
            std::cout << "Accion recibida: " << clientAction << std::endl;
            // Need to check if it's a valid JSON.
            nlohmann::json clientActionJson = nlohmann::json::parse(clientAction);
            int action = clientActionJson["action"].get<int>();
            if (action == CREATE_GAME_CODE){
                _isDead = (handleGameCreation(clientActionJson) &&
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
                int failJsonSize = failJsonString.size();
                clientSocket.sendMessage(&failJsonSize, REQUEST_LEN_SIZE);
                clientSocket.sendMessage(&failJsonString[0], failJsonSize);
            }
        } catch (std::runtime_error& e) {
            std::cout << e.what();
            // Client disconnected or the socket failed at some point.
            _isDead = true;
        } catch(...) {
            std::cout << "Excepcion inesperada\n";
            // Any other error.
            _isDead = true;
        }

    }
}

bool RoomWorker::handleGameCreation(nlohmann::json& actionData) {
    std::string gameName = actionData["gameName"].get<std::string>();
    bool result = roomManager.createGame(gameName);
    return result;
}

bool RoomWorker::handleJoinGame(nlohmann::json& actionData) {
    std::string gameName = actionData["gameName"].get<std::string>();
    std::string playerId = actionData["id"].get<std::string>();
    bool result = roomManager.addPlayerToGame(clientSocket, gameName, playerId);
    return result;
}