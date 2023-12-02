#include <iostream>
#include"Embedder.h"

using std::ofstream,std::ifstream, std::srand,std::time;

const char* inputFilePath = "../inputImage.bmp";
const char* outputPath = "../outputImage2.bmp";
int main(void)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    const char* key = generateRandomChar();

    const char* text = "Mahmut Ozer Gozukirmizi 1234657986";
    BMPHeader header;
    BMPHeader outputHeader;


    ifstream inputFile = openInputFile(inputFilePath);
    ofstream outputFile = openOutputFile(outputPath);

    inputFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    size_t inputFilePixelDataSize = header.fileSize - header.dataOffset;

    vector<char> inputFilePixelData(inputFilePixelDataSize);
    inputFile.read(inputFilePixelData.data(), inputFilePixelDataSize);
    inputFile.close();

    embedValue(inputFilePixelData, header, text);

    outputFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outputFile.write(inputFilePixelData.data(), inputFilePixelData.size());

    outputFile.close();

    ifstream outputFileReadMode = openInputFile(outputPath);
    outputFileReadMode.read(reinterpret_cast<char*>(&outputHeader), sizeof(BMPHeader));

    size_t outputFilePixelDataSize = outputHeader.fileSize - sizeof(BMPHeader);
    vector<char> outputFilePixelData(outputFilePixelDataSize);

    outputFileReadMode.read(outputFilePixelData.data(), inputFilePixelDataSize);
    getEmbodiedDataFromOutputFile(outputHeader, outputFilePixelData);



    outputFileReadMode.close();

    
    return 0;
}
