#include <iostream>
#include "Playfair.h"
#include <string>

using namespace std;

#define SIZE 30

int main()
{
    char key[SIZE];
    char* str;
    string plaintext;

    // New key to be encrypted
    strcpy(key, "Crypto");
    cout << "Key Text: " << key << endl;

    // Plain text
    plaintext = "This is an example plaintext created for the purpose of testing the playfair cipher used in the term project of the cryptography";
    cout << "Plain text: " << plaintext << endl;

    str = new char[plaintext.length() + 1];
    strcpy(str, plaintext.c_str());

    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << endl;

    // Convert cipher text to ASCII values and print them
    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

    delete[] str;

    return 0;
}

