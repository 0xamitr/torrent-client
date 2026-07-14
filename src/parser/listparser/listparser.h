#pragma once
#include <fstream>
#include <bencodevalue.h>

BencodeValue listParser(std::istream& file, InfoPos& pos);
