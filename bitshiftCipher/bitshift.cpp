#include <iostream>
#include <string>
#include <cstring> 
#include <vector>
#include <algorithm> 

using namespace std;

vector<int> bitshiftCipher(const char* message, const char* key) {
    int msgLen = strlen(message);
    int keyLen = strlen(key);

    string mutableKey(key);

    vector<int> encMessage;  // Vector to store the encrypted values.

    // Encryption happens inside this loop.
    for (int i = 0; i < msgLen; i++) {
        int msgAscii = static_cast<unsigned char>(message[i]); // Get the ASCII value of the message character.
        cout << "Debug >> Message ASCII: " << msgAscii << endl;

        // Perform encryption using the key.
        for (int k = 0; k < keyLen; k++) {
            int keyAscii = static_cast<unsigned char>(mutableKey[k]); // Get the ASCII value of the key character.
            cout << "Debug >> Key ASCII: " << keyAscii << endl;
            cout << "Debug >> Key char: " << mutableKey[k] << endl;

            // x = x + 3 << key % 8
            msgAscii = (msgAscii + 9) << (keyAscii % 5);
        }

        encMessage.push_back(msgAscii);

        // Reverse the key after each character.
        reverse(mutableKey.begin(), mutableKey.end());
    }

    return encMessage;
}

int main() {
    string message = "690129576"; // Define your message here
    string key = "CSE"; // Define your key here

    // Encrypt the message and get the encrypted ASCII values in a vector.
    vector<int> encryptedVector = bitshiftCipher(message.c_str(), key.c_str());

    // Print the ASCII values.
    cout << "ASCII values: ";
    for (int i : encryptedVector) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
