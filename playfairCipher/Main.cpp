#include <iostream>
#include "Playfair.h"

#define SIZE 30

using namespace std;


// Driver code
int main()
{
    char str[SIZE], key[SIZE];

    // Key to be encrypted
    strcpy(key, "Monarchy");
    cout << "Key Text: " << key << endl;

    // Plain text
    strcpy(str, "cagatay kahraman");
    cout << "Plain text: " << str << endl;

    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << endl;

    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

    return 0;
}