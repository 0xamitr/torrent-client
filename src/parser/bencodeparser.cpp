#include "listparser.h"
#include "dictparser.h"
#include "intparser.h"
#include "stringparser.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <bencodevalue.h>


BencodeValue benCodeParser(std::istream& file, InfoPos& pos) {
    BencodeValue result;
    if(file.peek() == 'e')
        return result;
    else if(file.peek() == 'd'){
        // std::cout << "reading dictionanry....."  << std::endl; 
        file.get();
        return dictParser(file, pos);
    }
    else if(file.peek() == 'i'){
        // std::cout << "reading integer......." << std::endl;
        file.get();
        return intParser(file, pos);
    }

    else if(file.peek() == 'l'){
        // std::cout << "reading list......" << std::endl;
        file.get();
        return listParser(file, pos);
    }
    else{
        // std::cout << "reading strings......" << std::endl;
        return stringParser(file, pos);
    }
}