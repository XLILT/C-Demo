#include <iostream>
#include <uuid/uuid.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "A.h"

using namespace std;

void f()
{
	cout << "f() is called." << endl;
}

int main()
{
	uuid_t uuid;
	char str[36] = {0};

	uuid_generate(uuid);
	uuid_unparse(uuid, str);

	boost::gregorian::date today = boost::gregorian::day_clock::local_day();

	cout << "hello cmake f(1, 1) = " << f(1, 1) << endl;
	cout << str << endl;
	cout << "today is: " << today << endl;

	boost::thread *thread_f = new boost::thread(boost::bind(&f));
	thread_f->join();
	delete thread_f;

	return 0;
}
