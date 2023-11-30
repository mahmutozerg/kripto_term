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
    strcpy(str, "instruments");
    cout << "Plain text: " << str << "\n";
 
    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);
    cout << "Cipher text: " << str << "\n";

    // Print each character's ASCII values
    vector<int> asciiValues = cipherTextToAsciiValues(str);
    printAsciiValues(asciiValues);

	return 0;
}