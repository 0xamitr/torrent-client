#include "parser/parser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
    cout << "Hello NotitTorrent";

    cout << "Reading Torrent file....................";
    ifstream inputFile("../A1454F1AFF699FB39F0E010AEC2D75637E7E76F9.torrent");

    if (!inputFile.is_open())
    {
        cout << " Erorr: Count not open the file" << endl;
    }

    string line;

    benCodeParser(inputFile);

    return 0;
}