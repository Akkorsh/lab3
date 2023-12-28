#include "TableTranspositionCipher.h"
#include <vector>
#include <stdexcept>
#include <cctype> // for std::toupper
#include <locale> // include locale for std::locale

TableTranspositionCipher::TableTranspositionCipher(int numColumns) :
    numColumns(numColumns)
{
    if (numColumns < 2) {
        throw(cipher_error("Invalid key"));
    }
}

std::wstring TableTranspositionCipher::encrypt(const std::wstring& plaintext)
{
    if (plaintext.empty()) {
        throw(cipher_error("Plaintext should not be empty"));
    }
    if (plaintext.find(' ') != std::wstring::npos) {
        throw(cipher_error("Plaintext should not contain spaces"));
    }

    std::wstring ciphertext;
    int numRows = (plaintext.length() + numColumns - 1) / numColumns;
    std::vector<std::wstring> table(numRows, std::wstring(numColumns, '*'));
    uint index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = numColumns - 1; j >= 0; j--) {
            if (index < plaintext.length()) {
                table[i][j] = std::toupper(plaintext[index]); // Convert to uppercase
                index++;
            }
        }
    }
    
    for (int j = 0; j < numColumns; j++) {
        for (int i = 0; i < numRows; i++) {
            ciphertext += table[i][j];
        }
    }
    return ciphertext;
}

std::wstring TableTranspositionCipher::decrypt(const std::wstring& ciphertext)
{
    if (ciphertext.empty()) {
        throw(cipher_error("Ciphertext should not be empty"));
    }
    if (ciphertext.find(' ') != std::wstring::npos) {
        throw(cipher_error("Ciphertext should not contain spaces"));
    }

    std::wstring decryptedText;
    int numRows = (ciphertext.length() + numColumns - 1) / numColumns;
    std::vector<std::wstring> table(numRows, std::wstring(numColumns, ' '));
    uint index = 0;
    for (int j = numColumns - 1; j >= 0; j--) {
        for (int i = 0; i < numRows; i++) {
            if (index < ciphertext.length()) {
                if (std::islower(ciphertext[index])) {
                    table[i][j] = std::tolower(ciphertext[index], std::locale()); // Convert to lowercase
                } else {
                    table[i][j] = ciphertext[index];
                }
                index++;
            }
        }
    }
    
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            decryptedText += table[i][j];
        }
    }
    return decryptedText;
}
