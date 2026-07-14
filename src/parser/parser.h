#pragma once
#include <fstream>
#include <bencodevalue.h>

// Just tell the compiler this function exists
BencodeValue benCodeParser(std::istream& file, InfoPos& info);

