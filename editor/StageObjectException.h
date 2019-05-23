//
// Created by camix on 23/05/19.
//

#ifndef PORTAL_STAGEOBJECTEX_H
#define PORTAL_STAGEOBJECTEX_H

#define EXC_INTRO "Couldn't add the tile: "
#define GRAVITY ". That's not a valid place for an object with physics laws!\n"
#define TAKEN_POSITION "That's not an empty position\n"
#define TO_SMALL_SPACE "The object does not fit in that space\n"



class StageObjectException : public std::exception {
protected:
    std::string& name;
public:
    explicit StageObjectException(std::string& name) : name(name) {}
};

class StageObjectAddTileGravityException : public StageObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + GRAVITY;
        return message.c_str();
    }

public:
    explicit StageObjectAddTileGravityException(std::string& name) :
            StageObjectException(name) {}
};

class StageObjectTakenPositionException : public StageObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + TAKEN_POSITION;
        return message.c_str();
    }

public:
    explicit StageObjectTakenPositionException(std::string& name) :
            StageObjectException(name) {}

};

class StageObjectToSmallSpaceException : public StageObjectException {
    virtual const char* what() const throw () {
        std::string message = EXC_INTRO + this->name + TO_SMALL_SPACE;
        return message.c_str();
    }

public:
    explicit StageObjectToSmallSpaceException(std::string& name) :
            StageObjectException(name) {}
};

#endif //PORTAL_STAGEOBJECTEX_H
