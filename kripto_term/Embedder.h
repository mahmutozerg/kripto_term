#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
using std::endl, std::cout,std::string,std::hex,std::vector,std::find,std::rand,std::stoi;
char endKey = '/';

void checkAndUpdateIfRowUnvalid(std::vector<long long int>& prevInsertedLocations, std::vector<char>& imagePixelData, long long int& i) {
    // Seed for random number generation
    int hexSizeUpperBound = getHexVal(imagePixelData.size()).size() + 1;

    while (std::any_of(prevInsertedLocations.begin(), prevInsertedLocations.end(),
        [&](long long int x) { return x >= i && x <= (i + hexSizeUpperBound); }))
    {
        i = std::rand() % (imagePixelData.size());
    }
}

void embedValue(vector<char>& imagePixelData, BMPHeader& header, const char* data)
{
    vector<long long int> prevInsertedLocations;
    string insertedLocationsHex;
    string currentHexValue;
    long long int index,nextIndex;


    index = (rand() % (int)(imagePixelData.size()));
    checkAndUpdateIfRowUnvalid(prevInsertedLocations, imagePixelData, index);
    currentHexValue = getHexVal(index);

    strncpy_s(header.start,currentHexValue.c_str(), currentHexValue.size());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {
        nextIndex = rand() % (int)(imagePixelData.size());
        checkAndUpdateIfRowUnvalid(prevInsertedLocations, imagePixelData, nextIndex);
        imagePixelData[index] = (char)(data[dataIndex++]);

        // Check for end of data

        if(data[dataIndex] != '\0')
        {
            currentHexValue = getHexVal(nextIndex);
            prevInsertedLocations.push_back(nextIndex);

            imagePixelData.erase(imagePixelData.begin() + index +1 , imagePixelData.begin() + index +1+ currentHexValue.size() );
            imagePixelData.insert(imagePixelData.begin() + index +1 , currentHexValue.begin(), currentHexValue.end());
            imagePixelData[index + 1 + currentHexValue.size()] = '*';

            index = nextIndex;

        }
        else
        {
            imagePixelData.erase(imagePixelData.begin() + index + 1, imagePixelData.begin() + index + 1 + currentHexValue.size());
            imagePixelData.insert(imagePixelData.begin() + index + 1, currentHexValue.begin(), currentHexValue.end());
            imagePixelData[index + 1 + currentHexValue.size()] = endKey;
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
        if (insertedLocationsHex.find(endKey) != string::npos)
        {
            unraveledData.push_back((insertedLocationsHex[0]));

            break;

        }
        else if (insertedLocationsHex.find('*') != string::npos && insertedLocationsHex.length()<=hexSizeUpperBound)
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