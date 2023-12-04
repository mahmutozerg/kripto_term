#pragma once

#include <random>
#include <string>
#include <vector>

using namespace std;

// Function to generate a secure key
string generateSecureKey(size_t length) {
    random_device rd;  // Cryptographically secure pseudo-random number generator
    uniform_int_distribution<int> dist(48, 57);

    string key;
    key.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        key.push_back(static_cast<char>(dist(rd)));
    }

    return key;
}

// XOR Encrypt/Decrypt Function
string xorEncryptDecrypt(const string& text, const string& key) {
    string result = text;

    // Perform XOR operation
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = text[i] ^ key[i];
    }

    return result;
}

// Function to convert encrypted string to ASCII values vector
vector<int> getAsciiValuesVector(const string& encryptedText) {
    vector<int> asciiValues;
    for (char c : encryptedText) {
        asciiValues.push_back(static_cast<int>(c));
    }
    return asciiValues;
}