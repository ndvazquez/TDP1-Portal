//
// Created by ndv on 6/15/19.
//

#ifndef PORTAL_SOCKET_H
#define PORTAL_SOCKET_H

#include <string>

#define ERROR_CODE -1
#define INVALID_FD -1

class WrongBindException : public std::exception {
    virtual const char* what() const throw() {
        return "It was imposible to bind";
    }
};

class NoAdressInformationException : public std::exception {
    virtual const char* what() const throw() {
        return "It was imposible to get information in the address";
    }
};

class WrongConnectionException : public std::exception {
    virtual const char* what() const throw() {
        return "It was imposible to connect";
    }
};

class DisconnectionWhileReceivingException : public std::exception {
    virtual const char* what() const throw() {
        return "The message couldn't be received given to a disconnection";
    }
};

class DisconnectionWhileSendingException : public std::exception {
    virtual const char* what() const throw() {
        return "The message couldn't be sent given to a disconnection";
    }
};

class Socket {
    int _fd;
    explicit Socket(int fileDescriptor);
    void _wrapperGetAddrinfo(std::string host, std::string port,
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

    void bindAndListen(std::string host, std::string port);
    void connectToHost(std::string host, std::string port);
    Socket acceptPeer();
    int receiveMessage(void *buffer, int size);
    int sendMessage(const void *buffer, int size);
    void shutdownAndClose();
};


#endif //PORTAL_SOCKET_H
