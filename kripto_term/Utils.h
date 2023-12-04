#pragma once
#include <sstream>
#include <iostream>
#include <set>
using std::string;
string getHexVal(long long int number)
{
    std::stringstream _stringStream;
    _stringStream << std::hex << number;

    return _stringStream.str();
}

const char * generateRandomChar()
{
    std::set<char> uniqueChars;

    while (uniqueChars.size() < 5) {
        char randomChar = static_cast<char>('a' + rand() % 26);
        uniqueChars.insert(randomChar);
    }

    char* result = new char[6]; 
    int i = 0;
    for (char c : uniqueChars) {
        result[i++] = c;
    }
    result[i] = '\0';

    return result;

}

