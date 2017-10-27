#include <string>
#include <map>

class Room
{
public:
    Room(const char *name)
        :room_name(name)
    {}

    ~Room() {}

public:
    std::string room_name;
};

class RoomManager
{
public:
    RoomManager() {}
    ~RoomManager();

    void create_room(const char *name);
    void destory_room(const char *name);

protected:
    std::map<std::string, Room*> room_map;
};
