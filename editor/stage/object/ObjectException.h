//
// Created by camix on 23/05/19.
//

#ifndef PORTAL_STAGEOBJECTEX_H
#define PORTAL_STAGEOBJECTEX_H

#include <iostream>

#define EXC_INTRO "Couldn't add the tile: "
#define GRAVITY ". That's not a valid place for an object with physics laws!\n"
#define TAKEN_POSITION "That's not an empty position\n"
#define FLOOR_NEEDED "The object above needs to be over a statick object\n"



class ObjectException : public std::exception {
protected:
    std::string& name;
public:
    explicit ObjectException(std::string& name) : name(name) {}
};

class AddTileGravityException : public ObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + GRAVITY;
        return message.c_str();
    }

public:
    explicit AddTileGravityException(std::string& name) :
            ObjectException(name) {}
};

class AddTileTakenPositionException : public ObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + TAKEN_POSITION;
        return message.c_str();
    }

public:
    explicit AddTileTakenPositionException(std::string& name) :
            ObjectException(name) {}

};

class RemoveTileFloorNeeded : public ObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + FLOOR_NEEDED;
        std::cerr << message;
        return message.c_str();
    }

public:
    explicit RemoveTileFloorNeeded(std::string& name) :
            ObjectException(name) {}
};

#endif //PORTAL_STAGEOBJECTEX_H
