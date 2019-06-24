//
// Created by camix on 24/06/19.
//

#ifndef PORTAL_SIMPLEINPUTMANAGER_H
#define PORTAL_SIMPLEINPUTMANAGER_H


#include "../common/InputText.h"

#include "CloseException.h"

class SimpleInputManager {
public:
    SimpleInputManager();
    ~SimpleInputManager();

    void start(InputText &input,
               Window &window,
               const char* secondOutput = "  ",
               const char* thirdOutputconst = "  ");
};


#endif //PORTAL_SIMPLEINPUTMANAGER_H
