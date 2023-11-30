#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "BMP.h"

using namespace std;

ifstream openInputFile(const char* filePath)
{
    ifstream inputFile(filePath, ios::binary);

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open the input file." << std::endl;
        exit(EXIT_FAILURE);
    }
    return inputFile;
}

ofstream openOutputFile(const char* filePath)
{
    ofstream outFile(filePath, ios::binary);

    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open the output file." << std::endl;
        exit(EXIT_FAILURE);
    }
    return outFile;
}
void checkAndUpdateIfRowUnvalid(vector<int> prevLocs,vector<char> imageData,int &i , int rowWidth)
{
    int rowStart = (i / rowWidth) * rowWidth;
    int rowEnd = rowStart + rowWidth - 1;

    while ((i < rowStart || i > rowEnd) || find(prevLocs.begin(), prevLocs.end(), i) != prevLocs.end()) // todo add prvloc check
    {
        i = rand() % (imageData.size() / 2);
        rowStart = (i / rowWidth) * rowWidth;
        rowEnd = rowStart + rowWidth - 1;
    }
}
void embedValue(vector<char>& imageData, BMPHeader& bmpHeader, const char** datas)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    vector<int> prevLocs;
    string insertedLocationsHex;
    int i;
    int numRows = bmpHeader.height;  
    int rowWidth = bmpHeader.width;

    int dataIndex = 0;

    for (int dataCounter = 0; datas[dataCounter] != nullptr; )
    {
         i = rand() % (imageData.size()/2);
         checkAndUpdateIfRowUnvalid(prevLocs, imageData,i,rowWidth);


        stringstream ss;
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
        imageData[i] = datas[dataCounter][dataIndex];
        cout<<"Data inserted to " << i << endl;
        dataIndex++;

        // Check for end of data
        if (datas[dataCounter][dataIndex] == '\0')
        {
            stringstream ss;
            dataIndex = 0;
            ss << hex << i;
            insertedLocationsHex.append(ss.str());
            insertedLocationsHex.append("EOL");
            ++dataCounter;
        }

        prevLocs.push_back(i);
    }

    i = rand() % (imageData.size() / 2);

    checkAndUpdateIfRowUnvalid(prevLocs,imageData,i,rowWidth);

    stringstream ss;
    ss << hex << i;
    insertedLocationsHex.append(ss.str());
    insertedLocationsHex.append("EOF");

    int randomInsertPos = rand() % ((imageData.size()/2));

    checkAndUpdateIfRowUnvalid(prevLocs, imageData, randomInsertPos, rowWidth);
    bmpHeader.start = randomInsertPos;
    cout << "Embedded data Inserted at Index  " << bmpHeader.start<<endl;

    // Erase the existing elements at the random position and insert the entire string
    imageData.erase(imageData.begin() + randomInsertPos, imageData.begin() + randomInsertPos + insertedLocationsHex.size());
    imageData.insert(imageData.begin() + randomInsertPos, insertedLocationsHex.begin(), insertedLocationsHex.end());

    // Update BMPHeader sizes
    bmpHeader.fileSize = sizeof(BMPHeader) + imageData.size();
    bmpHeader.imageSize = imageData.size() - bmpHeader.start;
}
void getEmbededDataFromOutputFile(BMPHeader& header, vector<char>& pixelData, const char* outputPath)
{
    string insertedLocationsHex;
    vector<char> rawData;
    unsigned long long  insertedLocationsInt;
    ifstream inp2 = openInputFile(outputPath);
    inp2.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    size_t pixelDataSize = header.fileSize - header.dataOffset;
    pixelData.resize(pixelDataSize);
    inp2.read(pixelData.data(), pixelDataSize);


    for (unsigned long long i = header.start; i < pixelData.size(); ++i)
    {
        insertedLocationsHex.append(1, pixelData[i]);
        if (insertedLocationsHex.find("EOF") != string::npos)
        {
            break;

        }

        if (insertedLocationsHex.find("EOL") != string::npos)
        {
            rawData.push_back(' ');
            insertedLocationsHex.clear();
        }

        if (insertedLocationsHex.find("NXT") != string::npos)
        {

            insertedLocationsInt = (stoi(insertedLocationsHex.substr(0, insertedLocationsHex.size() - 3), nullptr, 16));
            insertedLocationsHex.clear();
            rawData.push_back(pixelData[insertedLocationsInt]);
        }

    }

    for (auto c : rawData)
        cout << c;
    inp2.close();
}