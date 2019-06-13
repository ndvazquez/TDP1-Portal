//
// Created by camix on 12/06/19.
//

#ifndef PORTAL_BLOCKINGQUEUE_H
#define PORTAL_BLOCKINGQUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>

#define BQ_CLOSED_EXCEPTION "The queue is closed"

class BlockingQueue {
private:
    std::queue <std::vector<char>> queue;
    std::mutex m;
    std::condition_variable cond_variable;
    bool done;

public:
    BlockingQueue();
    ~BlockingQueue();

    //Guarda un elemento en la cola prioritaria.
    void push(std::vector<char>);

    //Saca un elemento de la cola prioritaria.
    //Si la cola esta vacia espera a que se ingrese un elemento.
    //Si se termino de encolar elementos se lanza una excepcion.
    std::vector<char> pop();

    //Cierra la cola.
    void close();
};



class BlockingQueueDoneException : public std::exception {
    virtual const char* what() const throw () {
        std::string message = BQ_CLOSED_EXCEPTION;
        return message.c_str();
    }

public:
    explicit BlockingQueueDoneException() = default;
};


#endif //PORTAL_BLOCKINGQUEUE_H
