#include <iostream>
#include "stringparser.h"
#include "parser.h"
#include <fstream>
#include "dictparser.h"

void dictParser(std::ifstream &file){

    if(file.peek() == 'e'){
        file.get();
        return;
    }
    else{
        int dictsize = file.get();
        while(dictsize){
            stringParser(file);
            benCodeParser(file);
            dictsize--;
        }
    }
}
