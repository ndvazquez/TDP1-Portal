//
// Created by ndv on 6/15/19.
//

#ifndef PORTAL_SOCKET_H
#define PORTAL_SOCKET_H

#include <string>

#define ERROR_CODE -1
#define INVALID_FD -1

class Socket {
    int _fd;
    explicit Socket(int fileDescriptor);
    int _wrapperGetAddrinfo(std::string host, std::string port,
                            struct addrinfo **ptr, int passive);
    int _socketCreate(int ai_family, int ai_socktype, int ai_protocol);
public:
    Socket();
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);
    Socket(const Socket&) =delete;
    Socket& operator=(const Socket&) =delete;
    ~Socket();
    bool isValid();

    //TODO: Aplicar manejo de excepciones a estas cosas.
    int bindAndListen(std::string host, std::string port);
    int connectToHost(std::string host, std::string port);
    Socket acceptPeer();
    int receiveMessage(void *buffer, int size);
    int sendMessage(const void *buffer, int size);
    void shutdownAndClose();
};


#endif //PORTAL_SOCKET_H
