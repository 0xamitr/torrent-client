#include <fstream>
#include "intparser.h"
#include <bencodevalue.h>

BencodeValue intParser(std::istream& file, InfoPos& pos){
    BencodeValue result;
    int num = 0;
    int sign = 1;
    if(file.peek() == '-')
        sign = -1;
    while(file.peek() != 'e'){
        num = num*10+file.get()-'0';
    }
    file.get();
    result.value = num;
    return result;
}