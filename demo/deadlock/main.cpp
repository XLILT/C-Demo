#include "stdafx.h"
#include <CommonBase/ThreadTool.h>

CSttLockCS lock1;
CSttLockCS lock2;

void f()
{
	CSttAutoLock gate1(lock1);
	SttSleep(10000);
	CSttAutoLock gate2(lock2);
}

void g()
{
	CSttAutoLock gate3(lock2);
	SttSleep(10000);
	CSttAutoLock gate4(lock1);
}

int main()
{
	
	boost::thread *t1 = new boost::thread(boost::bind(&f));
	boost::thread *t2 = new boost::thread(boost::bind(&g));
	//CSttAutoLock gate(lock1);
	
	t1->join();
	t2->join();

	return 0;
}

