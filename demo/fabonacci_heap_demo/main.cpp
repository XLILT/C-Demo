#include "stdafx.h"
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>

using namespace std;
using namespace boost::heap;

// PriorityQueue is expected to be a max-heap of integer values
template <typename PriorityQueue>
void ordered_iterator_interface(int data_size, int search_size)
{
    PriorityQueue pq;

    //pq.push(1);
    for (int i = 0; i < data_size; ++i)
    {
        pq.push(i);
    }

    typename PriorityQueue::ordered_iterator begin = pq.ordered_begin();
    typename PriorityQueue::ordered_iterator end = pq.ordered_end();

    cout << "Priority Queue: ordered iteration" << endl;
    int j = 0;

    uint64_t start = SttGetTickCount();

    for (typename PriorityQueue::ordered_iterator it = begin; it != end && j < search_size; ++it)
    {
        cout << *it << " "; // 3, 2, 1 (i.e. 1, 2, 3 in heap order)
        j++;
    }

    uint64_t stop = SttGetTickCount();

    cout << "cost: " << stop - start << endl;
}

template <typename T>
void test_tmplate(void)
{
    T c;
    cout << c << endl;
}

int main(int argc, char **argv)
{
    ordered_iterator_interface< boost::heap::fibonacci_heap<int> >(atoi(argv[1]), atoi(argv[2]));
    //test_tmplate<int>();
    return 0;
}
