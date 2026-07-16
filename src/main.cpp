#include "parser/parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bencodevalue.h>
#include <printbencode.h>
#include <openssl/sha.h>
#include "torrent/torrent.h"
#include "tracker/udptracker.h"

int main()
{
    InfoPos infopos;
    std::cout << "Hello NotitTorrent" << std::endl;
    std::cout << "Reading Torrent file...................." << std::endl;

    Torrent torrent = LoadTorrent("../A1454F1AFF699FB39F0E010AEC2D75637E7E76F9.torrent");

    std::cout << torrent.name << std::endl;

    std::vector<Peer> peer = udpTracker(torrent);
    std::cout << "peer size: " << peer.size() << std::endl;
    for (size_t i = 0; i < peer.size(); i++)
    {
        std::cout << "ip: "
                  << static_cast<int>(peer[i].ip[0]) << "."
                  << static_cast<int>(peer[i].ip[1]) << "."
                  << static_cast<int>(peer[i].ip[2]) << "."
                  << static_cast<int>(peer[i].ip[3]);

        std::cout << "  port: " << peer[i].port << '\n';
    }
    return 0;
}