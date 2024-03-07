#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Function to encrypt the plaintext using columnar cipher
std::string encryptColumnarCipher(const std::string& plaintext, const std::string& key) {
    std::string ciphertext;
    int keyLength = key.length();
    int plaintextLength = plaintext.length();
    int numRows = (plaintextLength + keyLength - 1) / keyLength;

    std::vector<std::string> matrix(numRows, std::string(keyLength, ' '));

    // Fill the matrix with the plaintext
    int index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < keyLength; j++) {
            if (index < plaintextLength) {
                matrix[i][j] = plaintext[index++];
            }
        }
    }

    // Sort the matrix columns based on the key
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());
    std::vector<int> order(keyLength);
    for (int i = 0; i < keyLength; i++) {
        order[i] = key.find(sortedKey[i]);
    }

    // Read the matrix column-wise to generate the ciphertext
    for (int i = 0; i < keyLength; i++) {
        for (int j = 0; j < numRows; j++) {
            ciphertext += matrix[j][order[i]];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using columnar cipher
std::string decryptColumnarCipher(const std::string& ciphertext, const std::string& key) {
    std::string plaintext;
    int keyLength = key.length();
    int ciphertextLength = ciphertext.length();
    int numRows = (ciphertextLength + keyLength - 1) / keyLength;

    std::vector<std::string> matrix(numRows, std::string(keyLength, ' '));

    // Calculate the number of empty cells in the last row
    int numEmptyCells = (numRows * keyLength) - ciphertextLength;

    // Sort the key to get the column order
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());
    std::vector<int> order(keyLength);
    for (int i = 0; i < keyLength; i++) {
        order[i] = key.find(sortedKey[i]);
    }

    // Fill the matrix with the ciphertext
    int index = 0;
    for (int i = 0; i < keyLength; i++) {
        for (int j = 0; j < numRows; j++) {
            if (j == numRows - 1 && i >= keyLength - numEmptyCells) {
                continue;  // Skip the empty cells in the last row
            }
            matrix[j][order[i]] = ciphertext[index++];
        }
    }

    // Read the matrix row-wise to generate the plaintext
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < keyLength; j++) {
            plaintext += matrix[i][j];
        }
    }

    return plaintext;
}

int main() {
    std::string plaintext = "Hello, World!";
    std::string key = "KEY";
    std:: cout << "Plain text:" << plaintext<< std::endl;
    std:: cout << "key:" << key<< std::endl;

    std::string ciphertext = encryptColumnarCipher(plaintext, key);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    std::string decryptedText = decryptColumnarCipher(ciphertext, key);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
