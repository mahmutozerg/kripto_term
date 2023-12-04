#pragma once
#include <sstream>
#include <iostream>
#include <set>
#include <random>  // for random number generation
#include <set>

using std::string,  std::random_device, std::mt19937, std::uniform_int_distribution, std::set;
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

void setRandomNumber(long long int& number, long long int maxNumber, long long int min_number = 0 )
{
    /*
    
      mt19937 is a random number engine in C++ from the <random> header. It's a Mersenne Twister pseudo-random number generator.
    */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long int> distribution(min_number, maxNumber );
    number = distribution(gen);
}
void checkAndUpdateIfRowInvalid(std::set<long long int>& prevInsertedLocations, int imagePixelDataSize, long long int& i) {
    int hexSizeUpperBound = getHexVal(imagePixelDataSize).size() + 1;

    for (auto location = prevInsertedLocations.begin(); location != prevInsertedLocations.end(); ++location) {
        // Ensure i is at least 8 units away from each element in prevInsertedLocations
        while (abs(i - *location) < 8) {
            setRandomNumber(i, imagePixelDataSize);
            location = prevInsertedLocations.begin();

        }

    }
}