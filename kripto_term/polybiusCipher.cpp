// CPP Program to implement polybius cipher
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// Function to encode text using the Polybius cipher and return an integer
void polybiusCipherEncode(string s) {
    unsigned long long encodedNumber = 0;

    for (char c : s) {
        int index = c - 'a';
        if (c >= 'j') index--; // Adjust index for 'j'

        int row = index / 5 + 1;
        int col = index % 5 + 1;

        // Constructing the encoded number
        encodedNumber = encodedNumber * 100 + (row * 10 + col);
    }

    cout << encodedNumber << endl;
}

// Function to encode text using the Polybius cipher and display the cipher text.
void polybiusCipher(string s) {
    string encodedString = "";
    unsigned long long encodedNumber = 0;
    int row, col, encodedInteger;

    // Convert each character to its encrypted code
    for (int i = 0; s[i]; i++) {

        // Finding row of the table
        row = ceil((s[i] - 'a') / 5) + 1;

        // Finding column of the table
        col = ((s[i] - 'a') % 5) + 1;

        // If character is 'k'
        if (s[i] == 'k') {
            row = row - 1;
            col = 5 - col + 1;
        }

        // If character is greater than 'j'
        else if (s[i] >= 'j') {
            if (col == 1) {
                col = 6;
                row = row - 1;
            }
            col = col - 1;
        }
        cout << row << col;
        encodedString += to_string(row) + to_string(col);
        encodedNumber = encodedNumber * 100 + (row * 10 + col);
        encodedInteger = encodedNumber % 128;
    }

    cout << endl;
    cout << "Encoded string: " << encodedString << endl;
    cout << "Encoded number: " << encodedNumber << endl;
    cout << "Encoded integer: " << encodedInteger << endl;
}

// Driver's Code
int main() {
    string s = "cagatay";
    polybiusCipher(s);
    return 0;
}