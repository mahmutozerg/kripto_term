#include <iostream>
#include "Playfair.h"

#define SIZE 30

using namespace std;



// Driver code
int main()
{
    char str[SIZE], key[SIZE];

    // Key to be encrypted
    strcpy(key, "Crypto");
    cout << "Key Text: " << key << endl;

    // Plain text
    strcpy(str, "This is an example text that is encrypted for the purpose of testing the playfair cipher created for the term project of the Cryptography lecture");
    cout << "Plain text: " << str << "\n";
 
    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << "\n";

    // Print each character's ASCII values
    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

	return 0;
}