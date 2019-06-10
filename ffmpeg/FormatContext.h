//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_FORMATCONTEXT_H
#define PORTAL_FORMATCONTEXT_H


#include <string>

class AVFormatContext;
class FormatContext {
public:
    // Ctor
    FormatContext();
    // Dtor
    ~FormatContext();
    AVFormatContext* getContext() const;
private:
    AVFormatContext *pFormatCtx;
};


#endif //PORTAL_FORMATCONTEXT_H
