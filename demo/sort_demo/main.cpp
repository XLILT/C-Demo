#include "stdafx.h"

using namespace std;

uint32_t sort(int size)
{
    vector<int> arr;
    for(int i = 0; i < size; i++)
    {
        arr.push_back(random());
    }

    uint64_t start_ts = SttGetTickCount();
    sort(arr.begin(), arr.end());
    uint64_t stop_ts = SttGetTickCount();

    cout << "size: " << size << " const: " << stop_ts - start_ts << endl;

    uint64_t start_ts2 = SttGetTickCount();
    sort(arr.begin(), arr.end());
    uint64_t stop_ts2 = SttGetTickCount();

    cout << "size: " << size << " const2: " << stop_ts2 - start_ts2 << endl;

    uint64_t start_ts3 = SttGetTickCount();
    sort(arr.begin(), arr.end());
    uint64_t stop_ts3 = SttGetTickCount();

    cout << "size: " << size << " const3: " << stop_ts3 - start_ts3 << endl;

    return stop_ts - start_ts;
}

int main(int argc, char *argv[])
{
    sort(atoi(argv[1]));
    return 0;
}
