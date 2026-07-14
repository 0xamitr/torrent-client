#include <memory>
#include <fstream>
#include "parser.h"
#include "listparser.h"
#include <bencodevalue.h>

BencodeValue listParser(std::istream& file, InfoPos& pos){
    List list;
    BencodeValue result;
    while(file.peek() != 'e'){
        list.push_back(std::make_unique<BencodeValue>(benCodeParser(file, pos)));
    }
    file.get();
    result.value = std::move(list);
    return result;
}