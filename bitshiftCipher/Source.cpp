#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

string customEncrypt(const char* message, const char* key) {
    int keyLen = strlen(key);
    int msgLen = strlen(message);

    vector<int> encMessage;  // Vector to store the encrypted values.

    char* reversedKey = new char[keyLen + 1];
    for (int i = 0; i < keyLen; i++) {
        reversedKey[i] = key[keyLen - 1 - i];
    }
    reversedKey[keyLen] = '\0'; // Add a null-pointer to the end of the string. This is needed as we used new to allocate memory to reversedKey variable, meaning it doesn't have a null-pointer by default.

    // Encryption happens inside this loop.
    for (int i = 0; i < msgLen; i++) {
        int asciiValue = static_cast<unsigned char>(message[i]); // Get the ASCII value of the character.

        // Add 9 as binary addition to the binary value of the character.
        bitset<8> asciiBinary(asciiValue);
        bitset<8> addedBinary(9);
        bitset<8> sumBinary = asciiBinary + addedBinary;

        // Convert the sum to an integer.
        int sumValue = static_cast<int>(sumBinary.to_ulong());

        const char* curKey; // Create a curKey variable to use the original or reversed key accordingly.
        if (i % 2 == 0) {
            curKey = key;  // If 'i' is even, use the original key.
        }
        else {
            curKey = reversedKey; // If 'i' is odd, use the reversed key.
        }

        // Get the ASCII value of the current key character (in decimal) modulo 8.
        int shiftAmount = curKey[0] % 8;

        // Perform the bitshift operation using keyAscii.
        for (int j = 0; j < shiftAmount; j++) {
            sumValue = (sumValue << 1) | ((sumValue >> 7) & 1); // Shift left by adding leading zeros.
        }

        encMessage.push_back(sumValue);
    }

    // Convert the encrypted values to a string.
    string encryptedString;
    for (int i : encMessage) {
        encryptedString += to_string(i) + " ";
    }

    // Remove the trailing space.
    encryptedString.pop_back();

    return encryptedString; // Return the encrypted string.
}

int main() {
    string message = "and"; // Define your message here
    string key = "YO"; // Define your key here

    // Encrypt the message and get the encrypted message in string form.
    string encryptedMessage = customEncrypt(message.c_str(), key.c_str());

    // Print the encrypted message.
    cout << "Encrypted message: " << encryptedMessage << endl;

    return 0;
}
