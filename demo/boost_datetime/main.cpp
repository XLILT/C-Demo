#include "stdafx.h"
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, char **argv)
{
    boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());
    cout << boost::posix_time::to_simple_string(t1) << endl;
    return 0;
}
