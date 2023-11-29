#include <iostream>

#include"DoSomething.h"

using namespace std;

const char* inputFilePath = "C:/Users/karak/Downloads/image.bmp";
const char* outputPath = "C:/Users/karak/Downloads/test2.bmp";



int main(void)
{

    const char* text[] = { "tst","Mahmutozergozukirmizi","erkek","kayseri","istanbul", nullptr};
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
    getOutputFileDataAfter(outputHeader, outputFilePixelData, outputPath);

    
    return 0;
}
