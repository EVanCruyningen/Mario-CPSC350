#ifndef FILE_PROCESSOR
#define FILE_PROCESSOR
/*
Basic Construstor and Destructor
inputParse takes in a filename and parses the necessary text in it to pass to gameRunner. This contains all the necessary info for level instantiation and Mario
outputToText takes in a string of the contents of the file and outputs a log.txt which contains the contents.
getValueArray() returns a pointer to the array of values
getValueAtPos() gets a value at a pos. Most commonly used for getting the number of levels
*/

/* 
This is what is in valueArray/dataArray.
Line # 1 is the number of levels, L (a positive integer)
Line # 2 is the dimension of the grid, N (a positive integer)
Line # 3 is the number of initial lives, V (a positive integer)
Line # 4 is the approximate percentage of the positions in each level with coins (a positive integer)
Line # 5 is the approximate percentage of the positions in each level with nothing (a positive integer)
Line # 6 is the approximate percentage of the positions in each level with Goombas (a positive integer)
Line # 7 is the approximate percentage of the positions in each level with Koopas (a positive integer)
Line # 8 is the approximate percentage of the positions in each level with mushrooms (a positive integer)
*/

#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include "Coordinate.h"

class FileProcessor{
    private:
        int *valueArray; //the array of inputText. Found from inputFile
     public: 
        FileProcessor();
        ~FileProcessor();
        void inputParse(std::string fileName);
        void outputToText(std::string fileContents);
        int* getValueArray();
        int getValueAtPos(int pos);
        std::string printInputFile();
};

#endif 