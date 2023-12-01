#pragma once
#include <sstream>
#include <iostream>

using std::string;
string getHexVal(long long int number)
{
    std::stringstream _stringStream;
    _stringStream << std::hex << number;

    return _stringStream.str();
}