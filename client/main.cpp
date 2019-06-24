///
// Created by ndv on 5/5/19.
//

#include <Drawer.h>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "Game.h"
#include "../common/SDLSession.h"
#include "../common/Window.h"

void playGame() {
    std::string idChell;

    std::string host = "localhost";
    std::string service = "8000";

    Socket clientSocket;
    clientSocket.connectToHost(host, service);
    Protocol clientProtocol(clientSocket);

    const int screenWidth = 1050;
    const int screenHeight = 700;
    std::string title = "Portal";
    Window newWindow(title, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    Game game(clientProtocol, clientSocket, newWindow);
    bool recorVideo;
    std::string videoPath;
    if (!game.play(idChell, &recorVideo, videoPath)) return;

    Drawer drawer(clientProtocol, clientSocket, newWindow);
    drawer.draw(idChell);
    std::cout << "Game finished, thanks for playing!\n";
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    try {
        playGame();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
