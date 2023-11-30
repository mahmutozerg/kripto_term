#include <iostream>
#include"Embedder.h"

using namespace std;

const char* inputFilePath = "../inputImage.bmp";
const char* outputPath = "../outputImage.bmp";

int main(void)
{

    const char* text[] = { "This is a ","Test Data","12345678910", nullptr};
    BMPHeader header;
    BMPHeader outputHeader;


    ifstream inputFile = openInputFile(inputFilePath);
    ofstream outputFile = openOutputFile(outputPath);

    inputFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    size_t inputFilePixelDataSize = header.fileSize - header.dataOffset;

    vector<char> inputFilePixelData(inputFilePixelDataSize);
    inputFile.read(inputFilePixelData.data(), inputFilePixelDataSize);

    embedValue(inputFilePixelData, header, text);

    outputFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outputFile.write(inputFilePixelData.data(), inputFilePixelData.size());

    outputFile.close();

    vector<char> outputFilePixelData;
    getEmbededDataFromOutputFile(outputHeader, outputFilePixelData, outputPath);

    
    return 0;
}
