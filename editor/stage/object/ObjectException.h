//
// Created by camix on 23/05/19.
//

#ifndef PORTAL_STAGEOBJECTEX_H
#define PORTAL_STAGEOBJECTEX_H

#include <iostream>

#define EXC_INTRO "Couldn't add the tile: "
#define GRAVITY "That's not a valid place for an object with physics laws!\n"
#define TAKEN_POSITION "That's not an empty position\n"
#define FLOOR_NEEDED "The object above needs to be over a statick object\n"
#define SET_NAME_EXC "Couldn't set the name: That name already exist in another object\n"
#define END_OF_STAGE "That's not a valid place for an object\n"


class ObjectException : public std::exception {
public:
    explicit ObjectException() = default;
};

class AddTileGravityException : public ObjectException {
public:
    const char* what() const noexcept override {
        return EXC_INTRO GRAVITY;
    }
    explicit AddTileGravityException() = default;
};

class AddTileTakenPositionException : public ObjectException {
public:
    const char* what() const noexcept override {
        return EXC_INTRO TAKEN_POSITION;
    }
    explicit AddTileTakenPositionException() = default;

};

class AddTileEndOfStageException : public ObjectException {
public:
    const char* what() const noexcept override {
        return EXC_INTRO END_OF_STAGE;
    }
    explicit AddTileEndOfStageException() = default;

};

class RemoveTileFloorNeeded : public ObjectException {
public:
    const char* what() const noexcept override {
        return EXC_INTRO FLOOR_NEEDED;
    }
    explicit RemoveTileFloorNeeded() = default;
};


class SetNameException : public ObjectException {
public:
    const char* what() const noexcept override {
        return EXC_INTRO SET_NAME_EXC;;
    }
    explicit SetNameException() = default;
};

#endif //PORTAL_STAGEOBJECTEX_H
