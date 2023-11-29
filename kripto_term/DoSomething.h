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
    size_t i = rand() % (imageData.size() / 100);
    int dataCounter = 0, dataIndex = 0;
    for (; i < imageData.size(); i = rand() % (imageData.size() / 100))
    {
        if (datas[dataCounter] != nullptr)
        {
            for (int j = 0; j < prevLocs.size(); ++j) {
                if (prevLocs[j] == i) {
                    // Number exists in the vector
                    i = rand() % (imageData.size() / 100);
                    j = 0;
                }
            }
            stringstream ss;
            ss << hex << i;
            insertedLocationsHex.append(ss.str());
            prevLocs.push_back(i);
            imageData[i] = datas[dataCounter][dataIndex];
            insertedLocationsHex.append("NXT");

            dataIndex++;

            if (datas[dataCounter][dataIndex] == '\0')
            {
                stringstream ss;

                dataIndex = 0;
                dataCounter++;
                ++i;
                ss << hex << i;

                insertedLocationsHex.append(ss.str());
                insertedLocationsHex.append("EOL");
            }
        }
        else
        {
            stringstream ss;

            dataIndex = 0;
            dataCounter++;
            ++i;
            ss << hex << i;
            insertedLocationsHex.append(ss.str());
            insertedLocationsHex.append("EOF");
            break;

        }

    }
    bmpHeader.start = imageData.size();

    for (auto c : insertedLocationsHex)
    {
        imageData.push_back(c);
    }

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

    std::vector<char> sequenceToFind = { '2', 'e', 'e' };

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