//
// Created by ndv on 6/13/19.
//

#include <iostream>
#include "StageManager.h"
#include "YamlParser.h"

StageManager::StageManager(int stageWidth,
        int stageHeight) :
        playerCounter(0),
        maxPlayers(2),
        stage(Stage(stageWidth, stageHeight)),
        parser("file.yaml", stage) {
    this->timeStamp = std::chrono::system_clock::now();
    parser.parseAndAdd();
}

StageManager::~StageManager() {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        it->second->stop();
        it->second->join();
        delete it->second;
    }
    for (auto it = clientQueues.begin(); it != clientQueues.end(); ++it) {
        delete it->second;
    }
}

void StageManager::run() {
    // We're gonna run a loop here, until a player wins the game or
    // everyone loses.
    // Also, I think it's a good idea to have the time step handled
    // here, because we can consume events between steps!
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        it->second->start();
    }

    nlohmann::json static_json = parser.getStaticJson();
    nlohmann::json dynamic_json = parser.getDynamicJson();

    for (auto it = clientQueues.begin(); it != clientQueues.end(); it++) {
        it->second->push(static_json.dump());
        it->second->push(dynamic_json.dump());
    }

    bool weGaming = true;
    while (weGaming) {
        auto end = std::chrono::system_clock::now();
        auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
                (end - timeStamp).count();
        if (difference <= 1000 / 60) {
            if (!userEventQueue.empty()){
                UserEvent userEvent = userEventQueue.pop();
                Chell* chell = stage.getChell(userEvent.getUserId());
                handleEvent(userEvent, chell);
            } else {
                std::this_thread::sleep_for (std::chrono::milliseconds(1));
            }
        } else {
            timeStamp = std::chrono::system_clock::now();
            stage.step();
            nlohmann::json stageStatus = stage.getCurrentState();
            // Check if any client is dead (disconnected).
            // If so, then delete his queue and the ClientHandler.
            for (auto it = clients.begin(); it != clients.end(); ){
                auto clientIt = it++;
                if (clientIt->second->isDead()) {
                    std::string playerID = clientIt->first;
                    std::cout << "Removing " + playerID << " from the client pool\n";
                    auto queueIt = clientQueues.find(playerID);
                    queueIt->second->push(THREAD_SUICIDE_PILL);
                    // Sanity check.
                    clientIt->second->stop();
                    clientIt->second->join();
                    delete queueIt->second;
                    clientQueues.erase(queueIt);
                    delete clientIt->second;
                    clients.erase(clientIt);
                    std::cout << "Client deleted\n";
                }
            }
            // Push stage status to each queue.
            // Doing a dump for each queue might be a performance hit.
            for (auto it = clientQueues.begin(); it != clientQueues.end(); it++) {
                it->second->push(stageStatus.dump());
            }
            // Provisory way to exit the loop.
            if (clients.size() == 0) {
                weGaming = false;
                std::cout << "Goodbye!\n";
            }
        }
    }
}

// This should use a factory but a switch will do for now.
void StageManager::handleEvent(UserEvent &userEvent,
        Chell *chell) {
    if (chell == nullptr || chell->hasWon() || chell->isDead()) return;
    std::string chell_id = userEvent.getUserId();
    int eventTypeCode = userEvent.getEventType();
    switch (eventTypeCode) {
        case USER_QUIT_CODE:
            chell->die();
            break;
        case USER_JUMP_CODE:
            chell->jump();
            break;
        case USER_MOVE_LEFT_CODE:
            chell->moveLeft();
            break;
        case USER_MOVE_RIGHT_CODE:
            chell->moveRight();
            break;
        case USER_STOP_CODE:
            chell->stop();
            break;
        case USER_DROP_ROCK:
            chell->downloadRock();
            break;
        case USER_GRAB_ROCK:
            {
                float x_chell = chell->getHorizontalPosition();
                float y_chell = chell->getVerticalPosition();
                Rock *rock = stage.getClosestRock(x_chell, y_chell);
                chell->grabRock(rock);
            }
            break;
        case USER_BLUE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                std::string replaced = "Chell";
                id.replace(0, replaced.length(), "BlueShot");
                stage.addShot(BLUE_SHOT_NAME, id, BULLET_HEIGHT, BULLET_WIDTH,
                        chell, target);
            }
            break;
        case USER_ORANGE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                std::string replaced = "Chell";
                id.replace(0, replaced.length(), "OrangeShot");
                stage.addShot(ORANGE_SHOT_NAME, id, BULLET_HEIGHT, BULLET_WIDTH,
                                  chell, target);
            }
            break;
        case USER_THROW_ROCK:
            chell->releaseRock();
            break;
        case USER_REMOVE_PORTAL:
            chell->removePortals();
            break;
        default:
            break;
    }
}

// For now we'll receive x and y to position Chell in stage.
bool StageManager::addPlayer(Socket &socket,
        const std::string& playerID) {
    // If there's a player with the same ID, then we can't add him.
    // Sanity check, if it's full we can't add players.
    if (isFull() || players.count(playerID) > 0) {
        return false;
    }
    ++playerCounter;
    std::string chellID = PLAYER_ID_PREFIX + std::to_string(playerCounter);
    StageStatusQueue* newStatusQueue = new StageStatusQueue();
    // Might have to check this code again,
    // if something fails it might corrupt the state of StageManager.
    // Send success message here, with the ChellId associated to playerId;
    players.insert({playerID, chellID});
    clientQueues.insert({chellID, newStatusQueue});
    clients.insert({chellID, new ClientHandler(socket,
            userEventQueue,
            *newStatusQueue)});
}

bool StageManager::isFull() {
    return playerCounter == maxPlayers;
}