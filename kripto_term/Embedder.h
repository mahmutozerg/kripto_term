#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
#include "Xor.h"
#include "Playfair.h"
using std::endl, std::cout,std::string,std::hex,std::vector,std::find,std::stoi;
const char endOfDataKey = ' ';


void embedValue(vector<char>& imagePixelData, BMPHeader& header, string data)
{

    set<long long int> prevInsertedLocations;
    string insertedLocationsHex;
    string nextHexValue;
    long long int index,nextIndex;

    setRandomNumber(index,imagePixelData.size());
    checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData.size(), index);
    nextHexValue = getHexVal(index);
    prevInsertedLocations.insert(index);

    strncpy_s(header.start,nextHexValue.c_str(), nextHexValue.length());

    for ( int dataIndex = 0; dataIndex < data.length(); )
    {
        imagePixelData[index] = (char)(data[dataIndex++]);
        setRandomNumber(nextIndex, imagePixelData.size());
        checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData.size(), nextIndex);
        prevInsertedLocations.insert(nextIndex);

        nextHexValue = getHexVal(nextIndex);
        imagePixelData.erase(imagePixelData.begin() + index + 1, imagePixelData.begin() + index + 1 + nextHexValue.length());
        imagePixelData.insert(imagePixelData.begin() + index + 1, nextHexValue.begin(), nextHexValue.end());
        imagePixelData[index + 1 + nextHexValue.length()] = endOfDataKey;

        index = nextIndex;



    }
    header.fileSize = sizeof(BMPHeader) + imagePixelData.size();
    header.imageSize = imagePixelData.size() ;
}

string getEmbodiedDataFromOutputFile(BMPHeader& header, vector<char>& imagePixelData)
{
    string insertedLocationsHex;
    string unraveledData;
    int nextIndex;
    int hexSizeUpperBound = getHexVal(imagePixelData.size()).size() + 1;

    for (unsigned long long i = stoi(header.start, nullptr,16); i < imagePixelData.size(); )
    {
        insertedLocationsHex.append(1, imagePixelData[i]);

        if (insertedLocationsHex.find(endOfDataKey) != string::npos && insertedLocationsHex.length()>=hexSizeUpperBound)
        {

            unraveledData.push_back((insertedLocationsHex[0]));
            insertedLocationsHex.erase(insertedLocationsHex.begin());
            nextIndex = (stoi(insertedLocationsHex, nullptr, 16));
            int c = insertedLocationsHex.size();
            insertedLocationsHex.clear();
            i = nextIndex;

        }
        else if (insertedLocationsHex.length() > hexSizeUpperBound)
            break;
        else
            ++i;
    }

    return unraveledData;

}