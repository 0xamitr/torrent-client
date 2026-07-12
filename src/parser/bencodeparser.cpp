#include "listparser.h"
#include "dictparser.h"
#include "intparser.h"
#include "stringparser.h"
#include "parser.h"
#include <iostream>
#include <string>

// Write your actual code here
void benCodeParser(std::ifstream& file) {
    std::cout << "\n[Parser] Successfully hooked into file stream!" << std::endl;
    // Your torrent parsing code goes here...
    if(file.peek() == 'e')
        return;
    else if(file.peek() == 'd'){
        std::cout << "reading...." << file.peek() << std::endl; 
        file.get();
        dictParser(file);
    }
    else if(file.peek() == 'i'){
        file.get();
        intParser(file);
    }

    else if(file.peek() == 'l'){
        file.get();
        listParser(file);
    }
    else{
        stringParser(file);
    }



    
    
}