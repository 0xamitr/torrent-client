#include <iostream>
#include <fstream>
#include <string>
#include "stringparser.h"

void stringParser(std::ifstream &file)
{   
    int num = 0;
    while (file.peek() != ':'){
        num = num*10 + file.get() - '0';
    }
    std::string str = "";
    while(num){
        str += file.get();
    }
}