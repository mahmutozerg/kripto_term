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
void xorEncryptDecrypt( string& text, const string& key) {


    for (size_t i = 0; i < text.size(); ++i) 
    {
        text[i] ^=  key[i];
    }

}

// Function to convert encrypted string to ASCII values vector
vector<int> getAsciiValuesVector(const string& encryptedText) {
    vector<int> asciiValues;
    for (char c : encryptedText) {
        asciiValues.push_back(static_cast<int>(c));
    }
    return asciiValues;
}