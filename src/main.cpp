#include "parser/parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bencodevalue.h>
#include <printbencode.h>
#include <openssl/sha.h>

int main()
{
    InfoPos infopos;
    std::cout << "Hello NotitTorrent" << std::endl;
    std::cout << "Reading Torrent file...................." << std::endl;

    std::ifstream inputFile("../A1454F1AFF699FB39F0E010AEC2D75637E7E76F9.torrent");

    if (!inputFile.is_open())
    {
        std::cout << " Erorr: Count not open the file" << std::endl;
    }

    std::string line;

    BencodeValue result = benCodeParser(inputFile, infopos);
    Dictionary &dict = std::get<Dictionary>(result.value);
    std::string createdby = std::get<std::string>((*dict.at("created by")).value);
    std::cout << "Created by: " << createdby << std::endl;
    std::int64_t creationdate = std::get<std::int64_t>((*dict.at("creation date")).value);
    std::cout << "Created on: " << creationdate << std::endl;

    Dictionary &info = std::get<Dictionary>((*dict.at("info")).value);
    std::int64_t length = std::get<std::int64_t>((*info.at("length")).value);
    std::int64_t piece_length = std::get<std::int64_t>((*info.at("piece length")).value);
    std::string name = std::get<std::string>((*info.at("name")).value);
    std::string pieces = std::get<std::string>((*info.at("pieces")).value);

    std::cout << "name: " << name << std::endl;
    std::cout << "length: " << length << std::endl;
    std::cout << "piece length: " << piece_length << std::endl;
    std::cout << "Pieces field size: "
              << pieces.size()
              << " bytes\n";

    inputFile.seekg(infopos.start);

    std::streamoff size = infopos.end - infopos.start;
    std::string rawInfo(static_cast<size_t>(size), '\0');

    inputFile.read(rawInfo.data(), infopos.end - infopos.start);

    std::cout << "Raw Info Size: " << rawInfo.size() << std::endl;

    std::cout.write(rawInfo.data(), 100) << std::endl;

    std::cout.write(rawInfo.data() + rawInfo.size() - 20, 20) << std::endl;

    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(
        reinterpret_cast<const unsigned char *>(rawInfo.data()),
        rawInfo.size(),
        hash);

    std::cout << "hash: " << hash << std::endl;
    return 0;
}