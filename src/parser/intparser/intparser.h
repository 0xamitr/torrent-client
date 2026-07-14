#pragma once
#include <fstream>
#include <bencodevalue.h>

BencodeValue intParser(std::istream& file, InfoPos& pos);
