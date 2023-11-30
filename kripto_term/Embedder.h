#include <vector>
#include <sstream>
#include <algorithm>
#include "FileOperations.h"
#include "BMP.h"
using std::endl, std::cout,std::string,std::hex,std::vector;


void checkAndUpdateIfRowUnvalid(std::vector<int> prevLocs,std::vector<char> imageData,int &i , int rowWidth)
{
    int rowStart = (i / rowWidth) * rowWidth;
    int rowEnd = rowStart + rowWidth - 1;

    while ((i < rowStart || i > rowEnd) || std::find(prevLocs.begin(), prevLocs.end(), i) != prevLocs.end()) // todo add prvloc check
    {
        i = rand() % (imageData.size() / 2);
        rowStart = (i / rowWidth) * rowWidth;
        rowEnd = rowStart + rowWidth - 1;
    }
}
void embedValue(std::vector<char>& imageData, BMPHeader& header, const char** datas)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> prevLocs;
    std::string insertedLocationsHex;
    int i;
    int numRows = header.height;
    int rowWidth = header.width;

    int dataIndex = 0;

    for (int dataCounter = 0; datas[dataCounter] != nullptr; )
    {
         i = std::rand() % (imageData.size()/2);
         checkAndUpdateIfRowUnvalid(prevLocs, imageData,i,rowWidth);


        std::stringstream ss;
        ss << hex << i;
        insertedLocationsHex.append(ss.str());
        insertedLocationsHex.append("NXT");

        /*
            #############################
            Asagidaki satir veriyi kyouyor  
        
            #############################
            imageData[i] = datas[dataCounter][dataIndex];
            datas[dataCounter][dataIndex] bu sifreli metin olacak
        */
        char a = (char)(datas[dataCounter][dataIndex]);
        imageData[i] = a;
        dataIndex++;

        // Check for end of data
        if (datas[dataCounter][dataIndex] == '\0')
        {
            std::stringstream ss;
            dataIndex = 0;
            ss << hex << i;
            insertedLocationsHex.append(ss.str());
            insertedLocationsHex.append("EOL");
            ++dataCounter;
        }

        prevLocs.push_back(i);
    }

    i = std::rand() % (imageData.size() / 2);

    checkAndUpdateIfRowUnvalid(prevLocs,imageData,i,rowWidth);

    std::stringstream ss;
    ss << hex << i;
    insertedLocationsHex.append(ss.str());
    insertedLocationsHex.append("EOF");

    int randomInsertPos = rand() % ((imageData.size()/2));

    checkAndUpdateIfRowUnvalid(prevLocs, imageData, randomInsertPos, rowWidth);
    strncpy_s(header.start, std::to_string(randomInsertPos).c_str(), std::to_string(randomInsertPos).size());
    cout << "Embedded data Inserted at Index  " << header.start<<endl;

    // Erase the existing elements at the random position and insert the entire string
    imageData.erase(imageData.begin() + randomInsertPos, imageData.begin() + randomInsertPos + insertedLocationsHex.size());
    imageData.insert(imageData.begin() + randomInsertPos, insertedLocationsHex.begin(), insertedLocationsHex.end());

    // Update BMPHeader sizes
    header.fileSize = sizeof(BMPHeader) + imageData.size();
    header.imageSize = imageData.size() ;
}
void getEmbededDataFromOutputFile(BMPHeader& header, std::vector<char>& pixelData)
{
    std::string insertedLocationsHex;
    std::vector<char> rawData;
    unsigned long long  insertedLocationsInt;


    for (unsigned long long i = std::stoi(header.start); i < pixelData.size(); ++i)
    {
        insertedLocationsHex.append(1, pixelData[i]);
        if (insertedLocationsHex.find("EOF") != std::string::npos)
        {
            break;

        }

        if (insertedLocationsHex.find("EOL") != std::string::npos)
        {
            rawData.push_back(' ');
            insertedLocationsHex.clear();
        }

        if (insertedLocationsHex.find("NXT") != std::string::npos)
        {

            insertedLocationsInt = (stoi(insertedLocationsHex.substr(0, insertedLocationsHex.size() - 3), nullptr, 16));
            insertedLocationsHex.clear();
            cout << "Reading data at " << insertedLocationsInt << " " <<pixelData[insertedLocationsInt] << endl;
            rawData.push_back((pixelData[insertedLocationsInt]));
        }

    }

    for (auto c : rawData)
        cout << c;
}