#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <iostream>
class TableTranspositionCipher
{
private:
    std::map <int, std::wstring> subNum; //ассоциативный массив "субстрока по номеру"
    std::map <int, std::wstring> resubNum; //ассоциативный массив "субстрока по номеру"
    int numColumns; //ключ
public:
    TableTranspositionCipher()=delete; //запретим конструктор без параметров
    TableTranspositionCipher(const int numColumns); //конструктор для установки ключа
    std::wstring encrypt(const std::wstring& plaintext); //зашифрование
    std::wstring decrypt(const std::wstring& ciphertext);//расшифрование
};
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
