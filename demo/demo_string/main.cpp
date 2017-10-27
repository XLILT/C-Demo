#include "stdafx.h"

const char * demo_str()
{
    std::string str("const string");
    str += " append";
    str += "input string";

    return str.c_str();
}

const char * demo_str2()
{
    std::string str("const");
    str += " string append";
    str += "input string";

    return str.c_str();
}

const char * demo_str3(const char *in_str)
{
    std::string str("const");
    str += " string append";
    str += in_str;

    return str.c_str();
}

int main(int argc, char **argv)
{
    cout << std::hex << static_cast<const void *>(demo_str()) << std::dec << endl;
    cout << std::hex << static_cast<const void *>(demo_str2()) << std::dec << endl;
    //cout << std::hex << static_cast<const void *>(demo_str3("input string")) << std::dec << endl;

    cout << std::hex << static_cast<const void *>(demo_str()) << std::dec << endl;
    cout << std::hex << static_cast<const void *>(demo_str2()) << std::dec << endl;
    //cout << std::hex << static_cast<const void *>(demo_str3("input string")) << std::dec << endl;

    return 0;
}
