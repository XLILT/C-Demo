#include <iostream>
#include "../lib_src/mylib.h"

int main(int argc, char **argv)
{
    RoomManager manager;

    while(true)
    {
        std::string name;
        std::cin >> name;
        if (name == " ")
        {
            break;
        }

        manager.create_room(name.c_str());
    }

    return 0;
}
