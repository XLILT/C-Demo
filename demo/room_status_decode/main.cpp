#include "stdafx.h"
//#include <netmsg/netmsg_gate.h>

//using namespace JXGate;

void encode_room_active(JXGate::MI_RoomActive2 *ra2, int counts)
{
    JXGate::RoomStatus rs;

    SttString sItem;
    rs.ToSttString(&sItem);

    for (int i = 0; i < counts; ++i)
    {
        ra2->rsa.push_back(rs);
    }
}

void test_room_active_cost(JXGate::MI_RoomActive2 *ra2, int counts)
{
    SttString ra2_str;
    ra2->ToTextMessage(&ra2_str);

    //printf("ra2_str:%s\n", ra2_str.c_UTF8());
    uint64_t start = SttGetTickCount();
    for (int i = 0; i < counts; ++i)
    {
        JXGate::MI_RoomActive2 tmp_ra2;
        tmp_ra2.FromTextMessage(ra2_str.c_UTF8());
    }

    uint64_t stop = SttGetTickCount();
    printf("decode %lu length room_active %u times cost %lums\n", ra2->rsa.size(), counts, stop - start);
}

int main(int argc, char **argv)
{
    JXGate::MI_RoomActive2 *ra2 = new JXGate::MI_RoomActive2;
    encode_room_active(ra2, atoi(argv[1]));

    test_room_active_cost(ra2, atoi(argv[2]));

    delete ra2;

    return 0;
}
