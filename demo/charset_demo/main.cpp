#include "stdafx.h"
#include <fstream>
#include <CommonBase/Unicode.h>

void demo_ostream()
{
    int x = 0xFF;

    std::ofstream ofs("b.txt", ios::binary);

    ofs.write(reinterpret_cast<char*>(&x), sizeof x);

    ofs.close();
}

void demo_wostream()
{
    std::locale oNewLocale("zh_CN.utf8");
    std::locale oPreviousLocale = std::locale::global( oNewLocale );

    std::wofstream wofs("wa.txt", ios::out);

    wofs << L"hello ofstream中文";

    wofs.close();

    std::locale::global( oPreviousLocale );
}

void demo_istream()
{
    std::ifstream ifs("a.txt");

    std::cout << ifs.rdbuf() << std::endl;

    ifs.close();
}

void demo_utf8_to_ucs()
{
    std::ofstream ofs("c.txt", ios::binary);

    //ofs<< "中国";
    str_ucs2 *ucs_str = GetUCS2FromUTF8("中国");

    ofs.write(reinterpret_cast<char*>(ucs_str), wcslen(ucs_str) * sizeof(str_ucs2));

    free(ucs_str);

    ofs.close();
}

void demo_ucs_to_utf8()
{
    std::ifstream ifs("c.txt", ios::binary | ios::ate);

    streamoff off = ifs.tellg();

    std::string str(off + 1, '\0');

    ifs.seekg(0);
    ifs.read(&str[0], off);

    str_utf8 *utf_str = GetUTF8FromUCS2(reinterpret_cast<str_ucs2 *>(&str[0]));

    std::cout << utf_str << std::endl;
    //std::cout << str << std::endl;

    free(utf_str);

    ifs.close();
}

int main(int argc, char **argv)
{
    demo_utf8_to_ucs();

    demo_ucs_to_utf8();

    return 0;
}
