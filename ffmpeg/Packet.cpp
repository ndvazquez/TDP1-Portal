//
// Created by camix on 10/06/19.
//

#include <iostream>
#include "Packet.h"

Packet::Packet() :
        pkt(av_packet_alloc()) {
    if (!pkt) {
        throw PacketInitException();
    }
}

AVPacket* Packet::get() {
    return pkt;
}

void Packet::write(FILE *outfile) {
    //esto es lento porque es escritura en disco
    fwrite(pkt->data, 1, pkt->size, outfile);
    av_packet_unref(pkt);
}

Packet::~Packet() {
    std::cerr << "entro a destruir el packet" << std::endl;
    av_packet_free(&pkt);
}
