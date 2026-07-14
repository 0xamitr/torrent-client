#pragma once
#include <fstream>
#include <bencodevalue.h>

BencodeValue dictParser(std::istream& file, InfoPos& pos);
