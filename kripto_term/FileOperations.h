#pragma once
#include <fstream>
#include <iostream>

std::ifstream openInputFile(const char* filePath)
{
    std::ifstream inputFile(filePath, std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        exit(EXIT_FAILURE);
    }
    return inputFile;
}

std::ofstream openOutputFile(const char* filePath)
{
    std::ofstream outFile(filePath, std::ios::binary);

    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        exit(EXIT_FAILURE);
    }
    return outFile;
}