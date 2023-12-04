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
    plaintext = "Halloween";
    cout << "Plain text: " << plaintext << endl;

    str = new char[2 * plaintext.length() + 1]; // Worst-case scenario
    strcpy(str, plaintext.c_str());

    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << endl;

    // Convert cipher text to ASCII values and print them
    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

     // Decipher back to plaintext
    decryptByPlayfairCipher(str, key);
    cout << endl << "Deciphered text: " << str << endl;

    delete[] str;

    return 0;
}