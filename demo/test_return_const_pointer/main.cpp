#include "stdafx.h"

const char * f1()
{
    char tmp[] = "123";
    return std::string(tmp).c_str();
}

int main(int argc, char **argv)
{
    std::cout << f1() << std::endl;

    return 0;
}
