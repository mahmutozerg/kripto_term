#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

// Convert all the characters to lowercase
void toLowerCase(char plain[], int ps)
{
	int i;
	for (i = 0; i < ps; i++) {
		if (plain[i] > 64 && plain[i] < 91)
			plain[i] += 32;
	}
}

// Remove all spaces in a string
// Can be extended to remove punctuation
int removeSpaces(char* plain, int ps)
{
	int i, count = 0;
	for (i = 0; i < ps; i++)
		if (plain[i] != ' ')
			plain[count++] = plain[i];
	plain[count] = '\0';
	return count;
}

// generates the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
	int i, j, k, flag = 0, * dicty;

	// a 26 character hashmap to store count of the alphabet
	dicty = (int*)calloc(26, sizeof(int));

	for (i = 0; i < ks; i++) {
		if (key[i] != 'j')
			dicty[key[i] - 97] = 2;
	}
	dicty['j' - 97] = 1;

	i = 0;
	j = 0;
	for (k = 0; k < ks; k++) {
		if (dicty[key[k] - 97] == 2) {
			dicty[key[k] - 97] -= 1;
			keyT[i][j] = key[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
	for (k = 0; k < 26; k++) {
		if (dicty[k] == 0) {
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}

// Search for the characters of a digraph in the key square and return their position
void search(char keyT[5][5], char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

// Function to find the modulus with 5
int mod5(int a)
{
	if (a < 0)
		a += 5;
	return (a % 5);
}

// Function to decrypt
void decrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];
	for (i = 0; i < ps; i += 2) {
		search(keyT, str[i], str[i + 1], a);
		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][mod5(a[1] - 1)];
			str[i + 1] = keyT[a[0]][mod5(a[3] - 1)];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[mod5(a[0] - 1)][a[1]];
			str[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

// Function to call decrypt
void decryptByPlayfairCipher(char str[], char key[])
{
	int ps, ks;
	char keyT[5][5];

	// Key
	ks = strlen(key);
	ks = removeSpaces(key, ks);
	toLowerCase(key, ks);

	// ciphertext
	ps = strlen(str);
	toLowerCase(str, ps);
	ps = removeSpaces(str, ps);

	generateKeyTable(key, ks, keyT);

	decrypt(str, keyT, ps);
}

/*
int prepare(char str[], int ptrs)
{
	if (ptrs % 2 != 0) {
		str[ptrs++] = 'z';
		str[ptrs] = '\0';
	}
	return ptrs;
}
*/

int newPrepare(char*& str) {
	string tempStr(str);

	for (size_t i = 0; i + 1 < tempStr.length(); i += 2) {
		// Avoid infinite loop by not inserting 'x' between two 'x's
		if (tempStr[i] == tempStr[i + 1] && tempStr[i] != 'x') {
			tempStr.insert(i + 1, "x");
		}
	}

	if (tempStr.length() % 2 != 0) {
		tempStr += 'z'; // Append bogus letter
	}

	delete[] str;
	str = new char[tempStr.length() + 1];
	strcpy(str, tempStr.c_str());

	return tempStr.length();
}


// Function for performing the encryption
void encrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];

	for (i = 0; i < ps; i += 2) {

		search(keyT, str[i], str[i + 1], a);

		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][mod5(a[1] + 1)];
			str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[mod5(a[0] + 1)][a[1]];
			str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

// Function to encrypt using Playfair Cipher
void encryptByPlayfairCipher(char str[], char key[])
{
	int ps, ks;
	char keyT[5][5];

	// Key
	ks = strlen(key);
	ks = removeSpaces(key, ks);
	toLowerCase(key, ks);

	// Plaintext
	ps = strlen(str);
	toLowerCase(str, ps);
	ps = removeSpaces(str, ps);

	char* tempStr = new char[2 * strlen(str) + 1];
	strcpy(tempStr, str);

	// Prepare plaintext
	ps = newPrepare(tempStr);

	strcpy(str, tempStr); // Copy the prepared string back to str

	// Free the temporary string
	delete[] tempStr;
	
	generateKeyTable(key, ks, keyT);

	encrypt(str, keyT, ps);
}

vector<int> cipherTextToAsciiValues(const string& str) {
	vector<int> asciiValues;

	// Convert each character to its ASCII value and store it in the vector
	for (char ch : str) {
		asciiValues.push_back(static_cast<int>(ch)); // ASCII value is automatically less than 128
	}

	return asciiValues;
}

void printAsciiValues(const vector<int>& asciiValues) {
	for (size_t i = 0; i < asciiValues.size(); i++) {
		cout << "ASCII Value " << i << ": " << asciiValues[i] << endl;
	}
}