#include <iostream>
#include <fstream>
#include <string>
#include "stringparser.h"
#include <bencodevalue.h>

BencodeValue stringParser(std::istream &file, InfoPos& pos)
{   
    BencodeValue result;
    int num = 0;
    while (file.peek() != ':' && file.peek() != EOF){
        num = num*10 + file.get() - '0';
    }
    file.get();
    std::string str = "";
    while(num--){
        str += file.get();
    }
    result.value = str;
    return result;
}