#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "Utils.h"
#include "BMP.h"
using std::endl, std::cout,std::string,std::hex,std::vector,std::find,std::rand,std::stoi;


void checkAndUpdateIfRowUnvalid(vector<long long int> prevInsertedLocations,vector<char> imageData,long long int &i)
{

    while (find(prevInsertedLocations.begin(), prevInsertedLocations.end(), i) != prevInsertedLocations.end())
    {
        i = static_cast<long long int>(rand() % (imageData.size() -1));
       
    }
}


void embedValue(vector<char>& imageData, BMPHeader& header, const char* data)
{
    vector<long long int> prevInsertedLocations;
    const vector<char> EOL({'E','O','L'});
    const vector<char> NXT({'N','X','T'});
    const vector<char> _EOF({'E','O','F'});
    string insertedLocationsHex;
    string currentHexValue;
    long long int index,nextIndex;


    index = (rand() % (int)(imageData.size()));
    checkAndUpdateIfRowUnvalid(prevInsertedLocations, imageData, index);
    currentHexValue = getHexVal(index);

    strncpy_s(header.start,currentHexValue.c_str(), currentHexValue.size());

    for ( int dataIndex = 0; data[dataIndex]!='\0'; )
    {
        
        nextIndex = rand() % (int)(imageData.size());
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






void getEmbodiedDataFromOutputFile(BMPHeader& header, vector<char>& pixelData)
{
    string insertedLocationsHex;
    vector<char> unraveledData;
    int nextIndex;


    for (unsigned long long i = stoi(header.start,0,sizeof(header.start)); i < pixelData.size(); )
    {
        insertedLocationsHex.append(1, pixelData[i]);
        if (insertedLocationsHex.find("EOF") != string::npos)
        {
            unraveledData.push_back((insertedLocationsHex[0]));

            break;

        }else if (insertedLocationsHex.find("NXT") != string::npos)
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