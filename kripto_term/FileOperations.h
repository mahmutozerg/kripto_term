#pragma once
#include <fstream>
#include <iostream>
using std::ifstream, std::ofstream,std::cerr,std::ios,std::endl;
ifstream openInputFile(const char* filePath)
{
    std::ifstream inputFile(filePath, ios::binary);

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open the input file." << endl;
        exit(EXIT_FAILURE);
    }
    return inputFile;
}
ofstream openOutputFile(const char* filePath)
{
    ofstream outFile(filePath, ios::binary);

    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open the output file." << endl;
        exit(EXIT_FAILURE);
    }
    return outFile;
}