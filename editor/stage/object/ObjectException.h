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
#define SET_NAME_EXC "That name already exist in another object"


class ObjectException : public std::exception {
public:
    explicit ObjectException() = default;
};

class AddTileGravityException : public ObjectException {
    const char* what() const noexcept override {
        return EXC_INTRO GRAVITY;
    }

public:
    explicit AddTileGravityException() = default;
};

class AddTileTakenPositionException : public ObjectException {
    const char* what() const noexcept override {
        return EXC_INTRO TAKEN_POSITION;
    }

public:
    explicit AddTileTakenPositionException() = default;

};

class RemoveTileFloorNeeded : public ObjectException {
    const char* what() const noexcept override {
        return EXC_INTRO FLOOR_NEEDED;
    }

public:
    explicit RemoveTileFloorNeeded() = default;
};


class SetNameException : public ObjectException {
    const char* what() const noexcept override {
        return EXC_INTRO SET_NAME_EXC;;
    }

public:
    explicit SetNameException() = default;
};

#endif //PORTAL_STAGEOBJECTEX_H
