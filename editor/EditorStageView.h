//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_EDITORSTAGEVIEW_H
#define PORTAL_EDITORSTAGEVIEW_H


#include <yaml-cpp/node/node.h>
#include <unordered_map>
#include <map>
#include "../common/Window.h"
#include "../common/Sprite.h"

#define GRAVITY_EXC "Couldn't add the tile, that's not a valid place for an object with physics laws!\n"
#define NAME_EXC "Couldn't add the tile, that's not a valid element!\n"
#define POSITION_EXC "Couldn't get tile's name, that's position is empty!\n"

class EditorStageViewAddTileNameException : public std::exception{
    virtual const char* what() const throw () {
        std::string message = NAME_EXC;
        return message.c_str();
    }
};
class EditorStageViewAddTileGravityException : public std::exception{
    virtual const char* what() const throw () {
        std::string message = GRAVITY_EXC;
        return message.c_str();
    }
};

class EditorStageViewEmptyPositionException : public std::exception{
    virtual const char* what() const throw () {
        std::string message = POSITION_EXC;
        return message.c_str();
    }
};

class EditorStageView {
private:
    Window& window;
    int factor;
    std::unordered_map<std::string, Sprite*> textures;
    std::map<std::pair<int, int>, std::string> tiles;
    std::map<std::string, bool> gravity;


public:
    EditorStageView(Window& window, YAML::Node& texturesInfo, int factor);
    ~EditorStageView();

    void draw(Window &window, SDL_Rect *camera, int xStart);

    void addTile(int x, int y, std::string &tileName);

    void removeTile(int x, int y);

    std::string &getName(int x, int y);
};


#endif //PORTAL_EDITORSTAGEVIEW_H
