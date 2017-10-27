#include "stdafx.h"

void erase_cost(int raw_size, int erase_size)
{
    list<int> raw_v(raw_size);
    list<int>::iterator it = raw_v.begin();
    advance(it, erase_size);

    cout << raw_v.size() << endl;

    uint64_t start = SttGetTickCount();
    raw_v.erase(raw_v.begin(), it);
    cout << raw_size << " - " << erase_size << " cost " << SttGetTickCount() - start << "ms" << endl;

    cout << raw_v.size() << endl;
}

void advance_cost(int raw_size, int adv_size)
{
    //vector<int> raw_v(raw_size);
    //vector<int>::const_iterator it = raw_v.begin();
    list<int> raw_v(raw_size);
    list<int>::const_iterator it = raw_v.begin();

    uint64_t start = SttGetTickCount();
    advance(it, adv_size);
    cout << raw_size << " --> " << adv_size << " cost " << SttGetTickCount() - start << "ms" << endl;
}

void copy_cost(int raw_size, int copy_size)
{
    //vector<int> raw_v(raw_size);
    //vector<int> raw_c(copy_size, 1);
    list<int> raw_v(raw_size);
    list<int> raw_c(copy_size, 1);

    cout << raw_v.size() << endl;

    uint64_t start = SttGetTickCount();
    //copy(raw_c.begin(), raw_c.end(), raw_v.begin());
    copy(raw_c.begin(), raw_c.end(), back_inserter(raw_v));
    cout << copy_size << " >> " << raw_size << " cost " << SttGetTickCount() - start << "ms" << endl;

    cout << raw_v.size() << endl;
}

void list_size_cost(int size)
{
    list<int> _list(size);
    uint64_t start = SttGetTickCount();
    _list.size();
    cout << size << " size " << " cost " << SttGetTickCount() - start << "ms" << endl;
    start = SttGetTickCount();
    _list.size();
    cout << size << " size " << " cost " << SttGetTickCount() - start << "ms" << endl;
}

int main(int argc, char **argv)
{
    //copy_cost(atoi(argv[1]), atoi(argv[2]));
    //advance_cost(atoi(argv[1]), atoi(argv[2]));
    //erase_cost(atoi(argv[1]), atoi(argv[2]));
    list_size_cost(atoi(argv[1]));

    return 0;
}
