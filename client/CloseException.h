//
// Created by camix on 24/06/19.
//

#ifndef PORTAL_CLOSEEXCEPTION_H
#define PORTAL_CLOSEEXCEPTION_H

#define CLOSED_EXC "The user want to close the process\n"

class CloseException: public std::exception {
public:
    CloseException() = default;
    virtual const char* what() const throw() {
        return CLOSED_EXC;
    }
};

#endif //PORTAL_CLOSEEXCEPTION_H
