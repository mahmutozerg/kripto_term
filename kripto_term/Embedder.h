#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
using std::endl, std::cout,std::string,std::hex,std::vector,std::find,std::rand,std::stoi;
const char endOfDataKey = ' ';

void checkAndUpdateIfRowInvalid(vector<long long int>& prevInsertedLocations, vector<char>& imagePixelData, long long int& i) {
    int hexSizeUpperBound = getHexVal(imagePixelData.size()).size() + 1;

    while (any_of(prevInsertedLocations.begin(), prevInsertedLocations.end(),
        [&](long long int x) { return x >= i && x <= (i + hexSizeUpperBound); }))
    {
        i = rand() % (imagePixelData.size());
    }
}

void embedValue(vector<char>& imagePixelData, BMPHeader& header, const char* data)
{
    vector<long long int> prevInsertedLocations;
    string insertedLocationsHex;
    string nextHexValue;
    long long int index,nextIndex;


    index = (rand() % (int)(imagePixelData.size()));
    checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData, index);
    nextHexValue = getHexVal(index);
    prevInsertedLocations.push_back(index);

    strncpy_s(header.start,nextHexValue.c_str(), nextHexValue.size());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {

        imagePixelData[index] = (char)(data[dataIndex++]);

        nextIndex = rand() % (int)(imagePixelData.size());
        checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData, nextIndex);

        nextHexValue = getHexVal(nextIndex);
        prevInsertedLocations.push_back(nextIndex);

        imagePixelData.erase(imagePixelData.begin() + index +1 , imagePixelData.begin() + index +1+ nextHexValue.size() );
        imagePixelData.insert(imagePixelData.begin() + index +1 , nextHexValue.begin(), nextHexValue.end());
        imagePixelData[index + 1 + nextHexValue.size()] = endOfDataKey;

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

    for (unsigned long long i = stoi(header.start,0,sizeof(header.start)); i < imagePixelData.size(); )
    {
        insertedLocationsHex.append(1, imagePixelData[i]);

        if (insertedLocationsHex.find(endOfDataKey) != string::npos && insertedLocationsHex.length()==hexSizeUpperBound)
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
        else
            ++i;
    }

    for (auto c : unraveledData) 
        cout << c;


}