#include "mylib.h"
#include <iostream>

RoomManager::~RoomManager(void)
{
    std::map<std::string, Room*>::iterator it = room_map.begin();
    while(it != room_map.end())
    {
        destory_room(it->first.c_str());
    }
}

void RoomManager::create_room(const char *name)
{
    if(room_map.find(name) == room_map.end())
    {
        room_map[name] = new Room(name);
        std::cout << "create room v5: " << name << std::endl;
    }
}

void RoomManager::destory_room(const char *name)
{
    std::map<std::string, Room*>::iterator it = room_map.find(name);
    if(it != room_map.end())
    {
        delete it->second;
        room_map.erase(it);
    }
}
