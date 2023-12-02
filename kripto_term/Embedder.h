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
    string currentHexValue;
    long long int index,nextIndex;


    index = (rand() % (int)(imagePixelData.size()));
    checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData, index);
    currentHexValue = getHexVal(index);

    strncpy_s(header.start,currentHexValue.c_str(), currentHexValue.size());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {
        nextIndex = rand() % (int)(imagePixelData.size());
        checkAndUpdateIfRowInvalid(prevInsertedLocations, imagePixelData, nextIndex);
        imagePixelData[index] = (char)(data[dataIndex++]);

        // Check for end of data

        if(data[dataIndex] != '\0')
        {
            currentHexValue = getHexVal(nextIndex);
            prevInsertedLocations.push_back(nextIndex);

            imagePixelData.erase(imagePixelData.begin() + index +1 , imagePixelData.begin() + index +1+ currentHexValue.size() );
            imagePixelData.insert(imagePixelData.begin() + index +1 , currentHexValue.begin(), currentHexValue.end());
            imagePixelData[index + 1 + currentHexValue.size()] = endOfDataKey;

            index = nextIndex;

        }
        else
        {

            imagePixelData[index + 1 ] = endOfDataKey;
            index = nextIndex;
        }


        prevInsertedLocations.push_back(index);
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
        if (insertedLocationsHex.find(endOfDataKey) != string::npos && insertedLocationsHex.length()==2)
        {
            unraveledData.push_back((insertedLocationsHex[0]));
            break;

        }
        else if (insertedLocationsHex.find(endOfDataKey) != string::npos && insertedLocationsHex.length()==hexSizeUpperBound)
        {
            unraveledData.push_back((insertedLocationsHex[0]));
            insertedLocationsHex.erase(insertedLocationsHex.begin());
            nextIndex = (stoi(insertedLocationsHex, nullptr, 16));
            int c = insertedLocationsHex.size();
            insertedLocationsHex.clear();
            i = nextIndex;

        }
        else
            ++i;
    }

    for (auto c : unraveledData) 
        cout << c;


}