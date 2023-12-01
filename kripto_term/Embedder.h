#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
using std::endl, std::cout,std::string,std::hex,std::vector;


void checkAndUpdateIfRowUnvalid(std::vector<int> prevInsertedLocations,std::vector<char> imageData,long long int &i)
{

    while ( std::find(prevInsertedLocations.begin(), prevInsertedLocations.end(), i) != prevInsertedLocations.end()) // todo add prvloc check
    {
        i = rand() % (imageData.size() / 2);
       
    }
}
void embedValue(std::vector<char>& imageData, BMPHeader& header, const char* data)
{
    std::vector<int> prevInsertedLocations;
    const std::vector<char> EOL({'E','O','L'});
    const std::vector<char> NXT({'N','X','T'});
    const std::vector<char> _EOF({'E','O','F'});
    std::string insertedLocationsHex;
    string currentHexValue;
    long long int index,nextIndex;


    index = (std::rand() % (int)(imageData.size()));
    checkAndUpdateIfRowUnvalid(prevInsertedLocations, imageData, index);
    currentHexValue = getHexVal(index);

    strncpy_s(header.start,currentHexValue.c_str(), currentHexValue.size());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {
        cout << index<<endl;
        
        nextIndex = std::rand() % (int)(imageData.size());
        checkAndUpdateIfRowUnvalid(prevInsertedLocations, imageData, nextIndex);
        imageData[index] = (char)(data[dataIndex++]);

        // Check for end of data

        if(data[dataIndex] != '\0')
        {
            currentHexValue = getHexVal(nextIndex);
            prevInsertedLocations.push_back(nextIndex);

            imageData.erase(imageData.begin() + index +1 , imageData.begin() + index +1+ currentHexValue.size() + NXT.size());
            imageData.insert(imageData.begin() + index +1 , currentHexValue.begin(), currentHexValue.end());
            imageData.insert(imageData.begin() + index +1+ currentHexValue.size(), NXT.begin(), NXT.end());

            index = nextIndex;

        }
        else
        {
            imageData.erase(imageData.begin() + index + 1, imageData.begin() + index + 1 + _EOF.size());
            imageData.insert(imageData.begin() + index + 1, _EOF.begin(), _EOF.end());
        }


        prevInsertedLocations.push_back(index);
    }
    header.fileSize = sizeof(BMPHeader) + imageData.size();
    header.imageSize = imageData.size() ;
}
void getEmbodiedDataFromOutputFile(BMPHeader& header, std::vector<char>& pixelData)
{
    std::string insertedLocationsHex;
    std::vector<char> unraveledData;
    int nextIndex;


    for (unsigned long long i = std::stoi(header.start,0,sizeof(header.start)); i < pixelData.size(); )
    {
        insertedLocationsHex.append(1, pixelData[i]);
        if (insertedLocationsHex.find("EOF") != std::string::npos)
        {
            unraveledData.push_back((insertedLocationsHex[0]));

            break;

        }else if (insertedLocationsHex.find("NXT") != std::string::npos)
        {
            nextIndex = (stoi(insertedLocationsHex.substr(1, insertedLocationsHex.size() - 3), nullptr, 16));
            int c = insertedLocationsHex.size();
            unraveledData.push_back((insertedLocationsHex[0]));
            insertedLocationsHex.clear();
            i = nextIndex;

        }
        else
            ++i;
    }

    for (auto c : unraveledData) 
        cout << c;


}