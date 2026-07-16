#include "parser/parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bencodevalue.h>
#include <printbencode.h>
#include <openssl/sha.h>
#include "torrent/torrent.h"

int main()
{
    InfoPos infopos;
    std::cout << "Hello NotitTorrent" << std::endl;
    std::cout << "Reading Torrent file...................." << std::endl;

    Torrent torrent = LoadTorrent("../A1454F1AFF699FB39F0E010AEC2D75637E7E76F9.torrent");

    std::cout << torrent.name << std::endl;
    
    return 0;
}