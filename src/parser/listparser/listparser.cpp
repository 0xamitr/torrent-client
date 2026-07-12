
#include <fstream>
#include "parser.h"
#include "listparser.h"

void listParser(std::ifstream& file){
    if(file.peek() == 'e')
        return;
    benCodeParser(file);
}