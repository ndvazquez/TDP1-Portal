//
// Created by cecix on 12/05/19.
//

#include <string>
#include <unordered_map>
#include <iostream>
#include <communication-support/Server.h>


int main(int argc, char* argv[]) {
    char c = '*';
    std::string host = "localhost";
    std::string service = "8000";
    try {
        Server server(host, service);
        server.start();
        while (c != 'q') {
            std::cin.get(c);
        }
        server.stop();
        server.join();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
