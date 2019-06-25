//
// Created by cecix on 12/05/19.
//

#include <string>
#include <unordered_map>
#include <iostream>
#include <communication-support/Server.h>
#define PORT_POS 1

void runServer(const std::string& port) {
    try {
        char c = '*';
        const std::string& host = "localhost";

        Server server(host, port);
        server.start();
        while (c != 'q') {
            std::cin.get(c);
        }
        server.stop();
        server.join();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid arguments.\nRun:\n./Server <port>\n";
        return -1;
    }
    const std::string& port = argv[PORT_POS];
    runServer(port);
    return 0;
}
