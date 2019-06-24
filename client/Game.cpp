//
// Created by cecix on 22/06/19.
//

#include <iostream>
#include "Game.h"
#include "../json/json.hpp"
#include "../common/constants.h"
#include "InitialMenu.h"
#include "../common/OutputText.h"
#include "LevelMenu.h"
#include "GameNameMenu.h"
#include "SimpleInputManager.h"

#define NO_LEVELS "NO LEVELS AVAILABLE AT THE MOMENT, CREATE ONE WITH THE EDITOR!"
#define INVALID_LEVEL_REQUEST "THE NAME YOU ENTERED WAS INVALID. ENTER A VALID LEVEL NAME"
#define LEVEL_REQUEST "ENTER A LEVEL NAME"

#define RECOR_REQUEST0 "DO YOU WANT TO RECORD THE GAME?"
#define RECOR_REQUEST1 "(N/y)"
#define RECOR_MESSAGE0 "SO... YOU WANT TO RECORD THE GAME"
#define RECOR_MESSAGE1 "JUST WRITE A NAME FOR THE FILE IN WHICH THE VIDEO WILL BE SAVED"


Game::Game(Protocol &clientProtocol, Socket &clientSocket, Window& window):
    clientProtocol(clientProtocol), clientSocket(clientSocket), window(window) {
}

bool Game::play(std::string &idChell, bool *recordGame, std::string &videoPath) {
    bool login = true;
    try {
        while (login) {
            // We'll first receive a list of games availables.
            std::string gaString = clientProtocol.receiveMessage();
            nlohmann::json gamesJson = nlohmann::json::parse(gaString);
            std::vector<std::string> gamesAvailable = gamesJson["games"].get<std::vector<std::string>>();
            std::string action;
            int rst;
            InitialMenu menu(window, gamesAvailable);
            rst = menu.start();

            if (rst == QUIT_ACTION) {
                clientSocket.shutdownAndClose();
                return false;
            }

            //We'll send the action to the server
            nlohmann::json actionJson;
            int actionCode;
            if (rst == CREATE_ACTION) {
                actionCode = CREATE_GAME_CODE;
            } else if (rst == JOIN_ACTION) {
                actionCode = JOIN_GAME_CODE;
            }
            actionJson["action"] = actionCode;
            std::string actionJsonString = actionJson.dump();
            clientProtocol.sendMessage(actionJsonString);

            OutputText message(window, " ");
            std::string levelPath;
            if (rst == CREATE_ACTION) {
                // Receive the available levels
                std::string laString = clientProtocol.receiveMessage();
                nlohmann::json levelsJson = nlohmann::json::parse(laString);
                std::vector<std::string> levelsAvailable = levelsJson["levels"].get<std::vector<std::string>>();
                if (levelsAvailable.empty()) {
                    std::string text = NO_LEVELS;
                    message.writeTheScreen(text);
                    clientSocket.shutdownAndClose();
                    return false;
                }
                LevelMenu option(window, levelsAvailable);
                levelPath = option.start(LEVEL_REQUEST);
                while (laString.find(levelPath) == std::string::npos || levelPath == ".yaml") {
                    levelPath = option.start(INVALID_LEVEL_REQUEST);
                }
            }

            // Prepare other fields needed to process
            GameNameMenu gameNameMenu(window, gaString);
            std::string gameName = gameNameMenu.start(rst);

            InputText idInput(window, "ENTER YOU ID" , GREEN_MOLD);
            std::string& playerId = idInput.getText();
            SimpleInputManager idManager;
            idManager.start(idInput, window);

            // DO_NOT_RECORD_GAME0 'n'
            // DO_NOT_RECORD_GAME1 'N'
            InputText recordRequest(window, RECOR_REQUEST0 , GREEN_MOLD);
            std::string& recordAnswer = recordRequest.getText();
            SimpleInputManager requestManager;
            requestManager.start(recordRequest, window, RECOR_REQUEST1);
            *recordGame = false;

            if(recordAnswer[0] == RECORD_GAME0 | recordAnswer[0] == RECORD_GAME1) {
                *recordGame = true;
                InputText record(window, RECOR_MESSAGE0, GREEN_MOLD);
                std::string &videoName = record.getText();
                SimpleInputManager inputManager;
                inputManager.start(record, window, RECOR_MESSAGE1);
                videoPath = VIDEO_DIRECTORY + videoName + VIDEO_EXTENSION;
            }

            nlohmann::json fieldsJson;
            fieldsJson["gameName"] = gameName;
            fieldsJson["id"] = playerId;
            std::string fieldJsonString = fieldsJson.dump();

            // Send the other fields to the server
            clientProtocol.sendMessage(fieldJsonString);

            if (rst == CREATE_ACTION) {
                // Send the level path to the client.
                clientProtocol.sendMessage(levelPath);
            }
            OutputText output(window, "WAITING RESPONSE FROM SERVER...");
            window.clear();
            window.drawBlackBackground();
            output.drawInTheCenter();
            window.render();

            std::string serverResponse = clientProtocol.receiveMessage();
            nlohmann::json serverResponseJson = nlohmann::json::parse(serverResponse);
            int responseCode = serverResponseJson["result"].get<int>();
            if (responseCode == SUCCESS_CODE) {
                idChell = serverResponseJson["idChell"].get<std::string>();
                login = false;
            }
        }
        return true;
    } catch (CloseException&) {
        clientSocket.shutdownAndClose();
        return false;
    }
}
