//
// Created by cecix on 12/05/19.
//

#include <unordered_map>
#include "Button.h"
#include "Gate.h"
#include "Stage.h"

int main(int argc, char* argv[]) {
    Stage stage(200, 200);

    std::unordered_map<std::string, Button*> buttons;
    b2Body* body1 = stage.addStaticRectangle(2, 2, 1, 1);
    b2Body* body2 = stage.addStaticRectangle(2, 2, 4, 4);
    b2Body* body3 = stage.addStaticRectangle(2, 2, 7, 7);
    b2Body* body_gate = stage.addStaticRectangle(2, 2, 10, 10);
    b2Body* body4 = stage.addStaticRectangle(2, 2, 13, 13);
    b2Body* body5 = stage.addStaticRectangle(2, 2, 16, 16);


    Button* button1 = new Button(body1);
    Button* button2 = new Button(body2);
    Button* button3 = new Button(body3);
    Button* button4 = new Button(body4);
    Button* button5 = new Button(body5);

    button3->activate();
    button2->activate();
    button4->activate();
    button5->activate();

    std::string id_button_1 = "Button1";
    std::string id_button_2 = "Button2";
    std::string id_button_3 = "Button3";
    std::string id_button_4 = "Button4";
    std::string id_button_5 = "Button5";

    buttons.insert({id_button_1, button1});
    buttons.insert({id_button_2, button2});
    buttons.insert({id_button_3, button3});
    buttons.insert({id_button_4, button4});
    buttons.insert({id_button_5, button5});

    std::string logic = "Button1 & (Button2 | Button3)) & (Button4 & Button5)";

    Gate* gate = new Gate(body_gate, logic, buttons);
    gate->update();

    return 0;
}
