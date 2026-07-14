#include <iostream>
#include "stringparser.h"
#include "parser.h"
#include <fstream>
#include "dictparser.h"
#include <bencodevalue.h>
#include <string>

BencodeValue dictParser(std::istream &file, InfoPos& pos)
{
    Dictionary dictionary;
    BencodeValue result;
    while (file.peek() != 'e')
    {
        std::string key = std::get<std::string>(stringParser(file, pos).value);
        if(key == "info")
            pos.start = file.tellg();
        dictionary[key] = std::make_unique<
            BencodeValue>(benCodeParser(file, pos));
        if(key == "info")
            pos.end = file.tellg();
    }
    file.get();
    result.value = std::move(dictionary);
    return result;
}
