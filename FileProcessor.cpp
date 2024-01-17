#include "FileProcessor.h"

FileProcessor::FileProcessor(){
    
}

FileProcessor::~FileProcessor(){
}
/**
 * Grab the number of columns in the entire thing. 
 * Make a monotonic stack for each column
 * Parse through entire file and push onto monotnic stack accordingly
 * End parse. Return output
*/
void FileProcessor::inputParse(std::string fileName){ 
    std::ifstream readFile(fileName);
    if (!(readFile.good())){
        std::cout << "Error, File Not Found. Please check spelling in main.cpp" << std::endl;
        return;
    }



}

void FileProcessor::outputToText(std::string fileContents){
    std::ofstream outputFile("log.txt");

    outputFile << fileContents;

    outputFile.close();
}