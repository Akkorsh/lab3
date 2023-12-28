// modAlphaCipher.h
#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <locale>
#include <codecvt>

class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::wstring lnumAlpha = L"абвгдеёжзийклмнопрмтуфхцчшщъыьэюя";
    std::map<wchar_t, int> alphaNum;
    std::vector<int> key;
    std::vector<int> convert(const std::wstring& s);
    std::wstring convert(const std::vector<int>& v);
    std::wstring getValidKey(const std::wstring& s);
    std::wstring toValidText(const std::wstring& s, std::string obj);
    bool is_rus(wchar_t wch);
    int is_low_rus(wchar_t wch);

public:
    modAlphaCipher() = delete;
    modAlphaCipher(const std::wstring& skey)
    {
        for (unsigned i = 0; i < numAlpha.size(); i++) {
            alphaNum[numAlpha[i]] = i;
        }
        key = convert(getValidKey(skey));
    }
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};

class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg) :
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) :
        std::invalid_argument(what_arg) {}
};
