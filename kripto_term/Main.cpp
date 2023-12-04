#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include"Embedder.h"

using std::ofstream,std::ifstream, std::srand,std::time;

const char* inputFilePath = "../hailmary.bmp";
const char* outputPath = "../outputImage2.bmp";
int main(void)
{
    string nameSurname = "MahmutUmurCagatayKriptoTermProjectPhase1Male";
    string ssn = "202312045";
    char keyForPlayFair[] = "TermProject";
    char* str;
  

    string key = generateSecureKey(ssn.length());

    str = new char[2 * nameSurname.length() + 1];
    strcpy(str, nameSurname.c_str());
    encryptByPlayfairCipher(str, keyForPlayFair);
    xorEncryptDecrypt(ssn, key);
    string full = str;
    full.push_back(' ');
    full = full + ssn;
    BMPHeader header;
    BMPHeader outputHeader;


    ifstream inputFile = openInputFile(inputFilePath);
    ofstream outputFile = openOutputFile(outputPath);

    inputFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    size_t inputFilePixelDataSize = header.fileSize - header.dataOffset;

    vector<char> inputFilePixelData(inputFilePixelDataSize);
    inputFile.read(inputFilePixelData.data(), inputFilePixelDataSize);
    inputFile.close();

    embedValue(inputFilePixelData, header, full);

    outputFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outputFile.write(inputFilePixelData.data(), inputFilePixelData.size());

    outputFile.close();

    /*
    ifstream outputFileReadMode = openInputFile(outputPath);
    outputFileReadMode.read(reinterpret_cast<char*>(&outputHeader), sizeof(BMPHeader));

    size_t outputFilePixelDataSize = outputHeader.fileSize - sizeof(BMPHeader);
    vector<char> outputFilePixelData(outputFilePixelDataSize);

    outputFileReadMode.read(outputFilePixelData.data(), inputFilePixelDataSize);
    string unraveled = getEmbodiedDataFromOutputFile(outputHeader, outputFilePixelData);
    outputFileReadMode.close();

    delete[]str;
    str = new char[2 * unraveled.length() + 1];
    strcpy(str, unraveled.substr(0,unraveled.find_first_of(' ')).c_str());

    decryptByPlayfairCipher(str,keyForPlayFair);
    string decryptedSsn = unraveled.substr(unraveled.find_first_of(' ') + 1, unraveled.length());
    xorEncryptDecrypt(decryptedSsn, key);

    cout << "Unraveled data " << str << " " << decryptedSsn;
    */
    return 0;
}    

