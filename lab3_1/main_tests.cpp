// main_tests.cpp
#include <UnitTest++/UnitTest++.h>
#include <string>
#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"А");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

// setup converter
using convert_type = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_type, wchar_t> converter;

SUITE(Costructor)
{

    TEST(NormalKey) {
        std::wstring wres = modAlphaCipher(L"ПРИВ").encrypt(L"ПППППППП");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ПРИАПРИА", res);
    }

    TEST(LowerlKey) {
        std::wstring wres = modAlphaCipher(L"га").encrypt(L"ТАКНС");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ГАГАГ", res);
    }

    TEST(LongKey) {
        std::wstring wres = modAlphaCipher(L"ДВЕРЬ").encrypt(L"ЛЕТО");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ДАЕР", res);
    }

    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp(L"32"), cipher_error);
    }

    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp(L"тпт.т"), cipher_error);
    }

    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L" ЛП "), cipher_error);
    }

    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""), cipher_error);
    }
}

SUITE(encrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres = p->encrypt(L"АОБПК");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ААААА", res);
    }

    TEST_FIXTURE(KeyB_fixture, LowerString) {
        std::wstring wres = p->encrypt(L"ЛМпк");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ААРЛ", res);
    }

    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"МАШИ НА"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->encrypt(L"МА,;.ШИНА"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->encrypt(L"АКТИВ553"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, Digits) {
        CHECK_THROW(p->encrypt(L"999"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }

    TEST(MaxStep) {
        std::wstring wres = modAlphaCipher(L"К").encrypt(L"ГРИЗЛИ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("КККККК", res);
    }
}

SUITE(decrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres = p->decrypt(L"КРАППСПКРК");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АААААААААА", res);
    }

    TEST_FIXTURE(KeyB_fixture, LowerString) {
    std::wstring wres = p->decrypt(L"КРМРКППКРР");
    std::string res = converter.to_bytes(wres);
    CHECK_EQUAL("АААААААААА", res);
	}

    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"М Н К Х С"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->decrypt(L".КАС.)"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->decrypt(L"КАРВ4РА21ИА"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, MaxStep) {
        std::wstring wres = modAlphaCipher(L"У").decrypt(L"КАКУК");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ННННН", res);
    }
}

int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}
