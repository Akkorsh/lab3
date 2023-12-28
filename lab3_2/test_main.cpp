#include <UnitTest++/UnitTest++.h>
#include <string>
#include "TableTranspositionCipher.h"
#include <locale>
#include <codecvt>
struct Key4_fixture {
    TableTranspositionCipher * p;
    Key4_fixture()
    {
        p = new TableTranspositionCipher(4);
    }
    ~Key4_fixture()
    {
        delete p;
    }
};
//setup converter
using convert_type = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_type, wchar_t> converter;

SUITE(Costructor)
{
    TEST(NormalKey) {
        std::wstring wres=TableTranspositionCipher(6).encrypt(L"ГРАНУЛЫ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("Л*У*Н*А*Р*ГЫ", res);
    }
    TEST(UselessKey) {
        CHECK_THROW(TableTranspositionCipher tb(1), cipher_error);
    }    
    TEST(NegativeKey) {
        CHECK_THROW(TableTranspositionCipher tb(-6), cipher_error);
    }
    TEST(LongKey) {
        std::wstring wres=TableTranspositionCipher(10).encrypt(L"ТЕЛЕЖКА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("***АКЖЕЛЕТ", res);
    }

}
SUITE(encrypt)
{
    TEST_FIXTURE(Key4_fixture, UpperString) {
        std::wstring wres=p->encrypt(L"ТЕЛЕФОН");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("Е*ЛНЕОТФ", res);
    }
    TEST_FIXTURE(Key4_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"ТЕ ЛЕ ФО Н"), cipher_error);
    }
    TEST_FIXTURE(Key4_fixture, PunctuationInString) {
        std::wstring wres=p->encrypt(L"Т.Е:;ЛЕФ(ОН");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL(":Ф*ЕЕН.ЛОТ;(", res);
    }
    TEST_FIXTURE(Key4_fixture, DigitsInString) {
        std::wstring wres=p->encrypt(L"ТЕЛ242Ф32ОН");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("23*ЛФНЕ2ОТ42", res);
    }
    TEST_FIXTURE(Key4_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L" "), cipher_error);
    }
    TEST(MainTest) {
        std::wstring wres=TableTranspositionCipher(7).encrypt(L"СПИШИГУЛЬ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("У*Г*И*Ш*И*ПЬСЛ", res);
    }
}
SUITE(decrypt)
{
    TEST_FIXTURE(Key4_fixture, UpperString) {
        std::wstring wres=p->decrypt(L"Е*ЛНЕОТФ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ТЕЛЕФОН*", res);
    }
    TEST_FIXTURE(Key4_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"ОФ* Е*ЛУ**Ф"), cipher_error);
    }
    TEST_FIXTURE(Key4_fixture, PunctuationInString) {
        std::wstring wres=p->decrypt(L":Ф*ЕЕН.ЛОТ;(");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("Т.Е:;ЛЕФ(ОН*", res);
    }
    TEST_FIXTURE(Key4_fixture, DigitsInString) {
        std::wstring wres=p->decrypt(L"23*ЛФНЕ2ОТ42");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ТЕЛ242Ф32ОН*", res);
    }
    TEST_FIXTURE(Key4_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L" "), cipher_error);
    }
    TEST(MainTest) {
        std::wstring wres=TableTranspositionCipher(7).decrypt(L"У*Г*И*Ш*И*ПЬСЛ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("СПИШИГУЛЬ*****", res);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
