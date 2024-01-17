#include <iostream>
#include "Level.h"
#include "FileProcessor.h"
#include "GameRunner.h"
#include "Coordinate.h"

int main(){
    std::string inputFileName = "inputFile.txt"; //change if you are inputting from a differently named file
    srand(time(NULL));
    FileProcessor* processor = new FileProcessor();
    processor->inputParse(inputFileName); 

    GameRunner* runner = new GameRunner(processor);
    
    runner->runGame();

    delete runner;
    delete processor;

    return 0;
}