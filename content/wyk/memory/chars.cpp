#include <iostream>

const char* prog = R"(
int main() {
    int x = 10;
    return x;
}
)";

int main()
{
    // char
    {
        char c = 'a';
        const char cstr[] = "hello";
        std::string str = "hello";
        std::cout << "sizeof(char) = " << sizeof(c) << ", sizeof(cstr) = " << sizeof(cstr) << ", str.length() = " << str.length() << std::endl;
        std::cout << c << " " << cstr << " " << str << " " << std::endl;
    }

    // wchar_t
    {
        wchar_t c = L'猫';
        const wchar_t cstr[] = L"こんにちは";
        std::wstring str = L"こんにちは";
        std::cout << "sizeof(wchar_t) = " << sizeof(c) << ", sizeof(cstr) = " << sizeof(cstr) << ", str.length() = " << str.length() << std::endl;
        std::wcout << c << cstr << str << std::endl;
    }

    // char16_t
    {
        char16_t c = u'猫';
        // char16_t c = u'🍌';
        const char16_t cstr[] = u"こんにちは";
        std::u16string str = u"こんにちは";
        std::cout << "sizeof(char16_t) = " << sizeof(c) << ", sizeof(cstr) = " << sizeof(cstr) << ", str.length() = " << str.length() << std::endl;
        // no standard output stream
    }

    // char32_t
    {
        char32_t c = U'猫';
        const char32_t cstr[] = U"🌍🚀🧑";
        std::u32string str = U"🌍🚀🧑";
        std::cout << "sizeof(char32_t) = " << sizeof(c) << ", sizeof(cstr) = " << sizeof(cstr) << ", str.length() = " << str.length() << std::endl;
        // no standard output stream
    }

    // char8_t
    {
        char8_t c = u8'a';
        // char8_t c = u8'猫';
        const char8_t cstr[] = u8"こんにちは";
        std::u8string str = u8"こんにちは";
        std::cout << "sizeof(char8_t) = " << sizeof(c) << ", sizeof(cstr) = " << sizeof(cstr) << ", str.length() = " << str.length() << std::endl;
        // no standard output stream
    }
}
