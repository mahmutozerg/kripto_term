#include <iostream>
#include "Playfair.h"

#define SIZE 30

using namespace std;

int main()
{
    char str[SIZE], key[SIZE];

    // Key used in encryption
    strcpy(key, "Crypto");
    cout << "Key Text: " << key << endl;

    // Plain text
    strcpy(str, "This is an example text that is used for the purpose of testing the playfair cipher implemented for the cryptography term project");
    cout << "Plain text: " << str << endl;

    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << endl;

    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

    return 0;
}