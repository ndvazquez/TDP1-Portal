//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_OUTPUT_H
#define PORTAL_OUTPUT_H

#include <string>
#include "Frame.h"
#include "Packet.h"
#include "FormatOutput.h"
#include "CodecContext.h"

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class FormatContext;
class SwsContext;
/**
 * Clase que encapsula lógica la salida de video
 * Se recomienda modularizar aun más esta clase, reforzando RAII
 */
class Output {
private:
    FormatContext& context;
    FormatOutput format;
    CodecContext codecContext;
    FILE* outputFile;
    Frame frame;
    Packet pkt;

public:
    // Ctor
    Output(FormatContext &context, const std::string &filename, Window &window);
    // Dtor
    ~Output();
    // Escribe un frame a disco. Utiliza `swsContext` para convertir
    // de RGB24 a YUV420p
    void writeFrame(const char* data, SwsContext* swsContext);
    // Cierra el stream de video
    void close();
};


#endif //PORTAL_OUTPUT_H
