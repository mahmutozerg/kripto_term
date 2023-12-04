#include <iostream>
#include <string>
#include <vector>
#include "Xor.h"

using namespace std;


int main() {
    string message = "690129576";  // Example message, up to 9 characters

    // Generate a key of the same length as the message
    string key = generateSecureKey(message.length());

    // Display the generated key
    cout << "Generated Key: ";
    for (char c : key) {
        cout << (int)c << " ";
    }
    cout << endl << endl;

    // Encrypt the message
    string encrypted = xorEncryptDecrypt(message, key);
    cout << "Encrypted: " << encrypted << endl;

    // Get ASCII values of the encrypted message
    vector<int> encAsciiValues = getAsciiValuesVector(encrypted);

    // Display the ASCII values
    cout << "ASCII values of encrypted message: ";
    for (int val : encAsciiValues) {
        cout << val << " ";
    }
    cout << endl << endl;

    // Decrypt the message
    string decrypted = xorEncryptDecrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    // Get ASCII values of the encrypted message
    vector<int> decAsciiValues = getAsciiValuesVector(decrypted);

    // Display the ASCII values
    cout << "ASCII values of decrypted message: ";
    for (int val : decAsciiValues) {
        cout << val << " ";
    }
    cout << endl;

    // Confirm that the decrypted message matches the original message
    cout << "Decryption successful: " << (message == decrypted ? "Yes" : "No") << endl;

    return 0;
}
