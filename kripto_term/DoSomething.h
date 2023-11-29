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

void embedValue(vector<char>& imageData, BMPHeader& bmpHeader, const char** datas)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    vector<int> prevLocs;
    string insertedLocationsHex;
    int i;
    int numRows = bmpHeader.height;  // Assuming you have a height field in your BMPHeader
    int rowWidth = bmpHeader.width;

    int dataIndex = 0;

    // Iterate through data to embed
    for (int dataCounter = 0; datas[dataCounter] != nullptr; )
    {
        // Calculate a random position within the image
         i = rand() % imageData.size();

        // Ensure that the random position does not cross row boundaries
        int rowStart = (i / rowWidth) * rowWidth;
        int rowEnd = rowStart + rowWidth - 1;

        while (i < rowStart || i > rowEnd)
        {
            i = rand() % imageData.size();
            rowStart = (i / rowWidth) * rowWidth;
            rowEnd = rowStart + rowWidth - 1;
        }

        // Convert index to hex and append to the string
        stringstream ss;
        ss << hex << i;
        insertedLocationsHex.append(ss.str());
        insertedLocationsHex.append("NXT");

        // Update the data
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
    i = rand() % imageData.size();

    stringstream ss;
    dataIndex = 0;
    ss << hex << i;
    insertedLocationsHex.append(ss.str());
    insertedLocationsHex.append("EOF");


    int randomInsertPos = rand() % imageData.size();
    bmpHeader.start = randomInsertPos;
    cout << "Inserted Indexes are " << bmpHeader.start<<endl;
    // Erase the existing elements at the random position and insert the entire string
    imageData.erase(imageData.begin() + randomInsertPos, imageData.begin() + randomInsertPos + insertedLocationsHex.size());
    imageData.insert(imageData.begin() + randomInsertPos, insertedLocationsHex.begin(), insertedLocationsHex.end());

    // Update BMPHeader sizes
    bmpHeader.fileSize += insertedLocationsHex.size();
    bmpHeader.imageSize += insertedLocationsHex.size();
}
void getOutputFileDataAfter(BMPHeader& header, vector<char>& pixelData, const char* outputPath)
{
    string insertedLocationsHex;
    unsigned long long  loc;
    ifstream inp2 = openInputFile(outputPath);
    inp2.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    size_t pixelDataSize = header.fileSize - header.dataOffset;
    pixelData.resize(pixelDataSize);
    inp2.read(pixelData.data(), pixelDataSize);


    for (unsigned long long i = header.start; i < pixelData.size(); ++i)
    {
        insertedLocationsHex.append(1, pixelData[i]);
        if (insertedLocationsHex.find("EOF") != string::npos)
            break;

        if (insertedLocationsHex.find("EOL") != string::npos)
        {
            cout << " ";
            insertedLocationsHex.clear();
        }

        if (insertedLocationsHex.find("NXT") != string::npos)
        {

            loc = (stoi(insertedLocationsHex.substr(0, insertedLocationsHex.size() - 3), nullptr, 16));
            insertedLocationsHex.clear();
            cout << pixelData[loc];
        }






    }
    inp2.close();
}