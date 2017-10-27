#include "stdafx.h"
#include <boost/detail/atomic_count.hpp>

int main(int argc, char **argv)
{
    boost::detail::atomic_count ato_count(0);

    cout << ++ato_count << endl;

    //ato_count = 0;
    cout << ++ato_count << endl;
    return 0;
}
