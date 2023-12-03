#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
#include <set>
#include <random>  // for random number generation

using std::endl, std::cout,std::string,std::hex,std::vector,std::find,std::stoi,std::random_device,std::mt19937,std::uniform_int_distribution,std::set;
const char endOfDataKey = ' ';

void checkAndUpdateIfRowInvalid(std::set<long long int>& prevInsertedLocations, int imagePixelDataSize, long long int& i) {
    int hexSizeUpperBound = getHexVal(imagePixelDataSize).size() + 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long int> distribution(0, imagePixelDataSize - 1);

    for (const long long int& location : prevInsertedLocations) {
        // Ensure i is at least 8 units away from each element in prevInsertedLocations
        while (abs(i - location) < 8) {
            i = distribution(gen);  // Generate a new random value for i
        }
    }
}
void embedValue(vector<char>& imagePixelData, BMPHeader& header, const char* data)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long int> distribution(0, imagePixelData.size() - 1);

    set<long long int> prevInsertedLocations;
    string insertedLocationsHex;
    string nextHexValue;
    long long int index,nextIndex;


    index = distribution(gen);
    checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData.size(), index);
    nextHexValue = getHexVal(index);
    prevInsertedLocations.insert(index);

    strncpy_s(header.start,nextHexValue.c_str(), nextHexValue.length());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {

        imagePixelData[index] = (char)(data[dataIndex++]);

        nextIndex = distribution(gen);
        checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData.size(), nextIndex);
        prevInsertedLocations.insert(nextIndex);

        nextHexValue = getHexVal(nextIndex);
        for (int i = index + 1,j=0; i < index + 1 + nextHexValue.length(); ++i,++j)
        {
            imagePixelData[i] = nextHexValue[j];
        }
        imagePixelData[index + 1 + nextHexValue.length()] = endOfDataKey;

        index = nextIndex;



    }
    header.fileSize = sizeof(BMPHeader) + imagePixelData.size();
    header.imageSize = imagePixelData.size() ;
}






void getEmbodiedDataFromOutputFile(BMPHeader& header, vector<char>& imagePixelData)
{
    string insertedLocationsHex;
    vector<char> unraveledData;
    int nextIndex;
    int hexSizeUpperBound = getHexVal(imagePixelData.size()).size() + 1;

    for (unsigned long long i = stoi(header.start, nullptr,16); i < imagePixelData.size(); )
    {
        insertedLocationsHex.append(1, imagePixelData[i]);

        if (insertedLocationsHex.find(endOfDataKey) != string::npos && insertedLocationsHex.length()>=hexSizeUpperBound)
        {
            try
            {
                unraveledData.push_back((insertedLocationsHex[0]));
                insertedLocationsHex.erase(insertedLocationsHex.begin());
                nextIndex = (stoi(insertedLocationsHex, nullptr, 16));
                int c = insertedLocationsHex.size();
                insertedLocationsHex.clear();
                i = nextIndex;

            }
            catch (...)
            {
                break;
            }


        }
        else if (insertedLocationsHex.length() > hexSizeUpperBound)
        {
            break;
        }else
            ++i;
    }

    for (auto c : unraveledData) 
        cout << c;

    imagePixelData[12121] = 1;
}