#pragma once
#include <fstream>
#include <bencodevalue.h>

BencodeValue stringParser(std::istream &file, InfoPos& pos);
