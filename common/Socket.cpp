//
// Created by ndv on 6/15/19.
//

#include "Socket.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <stdexcept>

void Socket::_wrapperGetAddrinfo(std::string host, std::string port,
                                struct addrinfo **ptr,
                                int passive){
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = passive ? AI_PASSIVE : 0;

    int s = getaddrinfo(host.c_str(), port.c_str(), &hints, &res);
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        freeaddrinfo(*ptr);
        throw NoAdressInformationException();
    }
    *ptr = res;
}

int Socket::_socketCreate(int ai_family, int ai_socktype, int ai_protocol){
    int fd = socket(ai_family, ai_socktype, ai_protocol);
    return fd;
}

Socket::Socket(){
    this->_fd = INVALID_FD;
}

Socket::Socket(int fileDescriptor) : _fd(fileDescriptor){}

Socket::Socket(Socket&& other){
    this->_fd = other._fd;
    other._fd = INVALID_FD;
}

Socket& Socket::operator=(Socket&& other){
    if (this == &other){
        return *this;
    }
    this->_fd = other._fd;
    other._fd = INVALID_FD;
    return *this;
}

void Socket::shutdownAndClose(){
    if (this->_fd != INVALID_FD){
        shutdown(this->_fd, SHUT_RDWR);
        close(this->_fd);
    }
}

Socket::~Socket(){
    shutdownAndClose();
}

void Socket::bindAndListen(std::string host, std::string port){
    struct addrinfo *res = nullptr;
    _wrapperGetAddrinfo(host, port, &res, 1);
    bool did_we_managed_to_bind = false;
    struct addrinfo *ptr;
    for (ptr = res; ptr && !did_we_managed_to_bind; ptr = ptr->ai_next){
        this->_fd =_socketCreate(ptr->ai_family, ptr->ai_socktype,
                                 ptr->ai_protocol);
        if (this->_fd == INVALID_FD) {
            continue;
        }
        int v = 1;
        int s = setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(v));
        if (s == ERROR_CODE) {
            printf("Error: %s\n", strerror(errno));
            close(this->_fd);
            continue;
        }

        s = bind(this->_fd, ptr->ai_addr, ptr->ai_addrlen);
        if (s == ERROR_CODE) {
            printf("Error: %s\n", strerror(errno));
            close(this->_fd);
            continue;
        }

        s = listen(this->_fd, 10);
        if (s == ERROR_CODE) {
            printf("Error: %s\n", strerror(errno));
            close(this->_fd);
            continue;
        }
        did_we_managed_to_bind = (s != ERROR_CODE);
    }
    freeaddrinfo(res);
    if (! did_we_managed_to_bind) throw WrongBindException();
}

void Socket::connectToHost(std::string host, std::string port){
    struct addrinfo *res = NULL;
    _wrapperGetAddrinfo(host, port, &res, 0);

    struct addrinfo *ptr;
    bool are_we_connected = false;
    for (ptr = res; ptr && !are_we_connected; ptr = ptr->ai_next){
        this->_fd =_socketCreate(ptr->ai_family, ptr->ai_socktype,
                                 ptr->ai_protocol);
        if (this->_fd == INVALID_FD){
            continue;
        }
        int s = connect(this->_fd, res->ai_addr, res->ai_addrlen);
        if (s == ERROR_CODE) {
            printf("Error: %s\n", strerror(errno));
            close(this->_fd);
            continue;
        }
        are_we_connected = (s != ERROR_CODE);
    }
    freeaddrinfo(res);
    if (! are_we_connected) throw WrongConnectionException();
}

int Socket::receiveMessage(void *buffer, int size){
    char* cBuffer = (char*) buffer;
    int s = 0;
    int received = 0;
    while (received < size) {
        s = recv(this->_fd, &cBuffer[received], size-received, MSG_NOSIGNAL);
        if (s == 0) {
            throw DisconnectionWhileReceivingException();
        } else if (s < 0) {
            // TODO: Change this exception to something along the lines of UnexpectedError.
            throw DisconnectionWhileReceivingException();
        } else {
            received += s;
        }
    }
    return received;
}

int Socket::sendMessage(const void *buffer, int size){
    char* cBuffer = (char*) buffer;
    int s = 0;
    int sent = 0;
    bool is_the_socket_still_valid = true;

    while (sent < size && is_the_socket_still_valid){
        s = send(this->_fd, &cBuffer[sent], size-sent, MSG_NOSIGNAL);
        if (s == 0) {
            is_the_socket_still_valid = false;
        } else if (s < 0) {
            throw DisconnectionWhileSendingException();
        } else {
            sent += s;
        }
    }
    if (is_the_socket_still_valid) return sent;
    throw DisconnectionWhileSendingException();
}

Socket Socket::acceptPeer(){
    int peer_fd = accept(this->_fd, nullptr, nullptr);
    return std::move(Socket(peer_fd));
}

bool Socket::isValid(){
    return this->_fd != INVALID_FD;
}
