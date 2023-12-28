// modAlphaCipher.cpp
#include "modAlphaCipher.h"

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

std::wstring modAlphaCipher::toValidText(const std::wstring& s, std::string obj)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Empty " + obj);
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    obj[0] = std::toupper(obj[0]); // Convert the first character of the object to uppercase
    for (auto& c : tmp) {
        if (!is_rus(c))
            throw cipher_error(obj + " has invalid symbols: " + st);
        if (is_low_rus(c) != -1)
            c = numAlpha[is_low_rus(c)];
    }
    return tmp;
}

std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    std::wstring tmp(s);
    if (s.empty()) {
        throw cipher_error("Empty key");
    }
    std::locale loc("ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    tmp = codec.from_bytes(std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(s));

    // Convert the key to uppercase
    for (auto& c : tmp) {
        c = std::toupper(c, loc);
        if (!isalpha(c, loc) || islower(c, loc)) {
            throw cipher_error("Invalid key");
        }
    }
    return tmp;
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text(open_text);
    std::wstring valid_text = toValidText(text, "string");
    std::vector<int> work = convert(valid_text);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text(cipher_text);
    std::wstring valid_text = toValidText(text, "string");
    std::vector<int> work = convert(valid_text);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

bool modAlphaCipher::is_rus(wchar_t wch)
{
    std::wstring alf = lnumAlpha + numAlpha;
    for (uint i = 0; i < alf.length(); i++) {
        if (wch == alf[i])
            return true;
    }
    return false;
}

int modAlphaCipher::is_low_rus(wchar_t wch)
{
    for (uint i = 0; i < lnumAlpha.length(); i++) {
        if (wch == lnumAlpha[i])
            return i;
    }
    return 0;
}
