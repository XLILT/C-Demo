#include <stdio.h>
#include <iostream>
#include <memory>
//#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace std;

struct A
{
	boost::shared_ptr<int> p;
};

void f(boost::shared_ptr<int> &x)
{
	sleep(2);
	cout << *x << endl;
}

void test_bool()
{
	boost::shared_ptr<void> p;
	if (p)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	p = boost::shared_ptr<void>(new char);
	if (p)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}

int main()
{
	/*
	std::auto_ptr<int> auto_tmp(new int(25));
	std::shared_ptr<int> share_tmp(new int(25));
	boost::shared_ptr<int> b_share_temp(new int(25));

	auto ptr = []()
    	{
        	std::cout << "hello world" << std::endl;
    	};

	auto i = 25;

	A *a = new A;
	boost::shared_ptr<int> b_share_temp(new int(25));

	a->p = b_share_temp;

	if(a)
	{
	    delete a;
	}
	*/

	/*
	int *p = new int(3);
	{
		boost::shared_ptr<int> tmp(p);
	}

	printf("%d\n", *p);
	int *q = NULL;
	delete q;
	*/

	//boost::shared_ptr<int> b_share_temp(new int(25));

	//f(b_share_temp);
	//boost::thread *t = new boost::thread(boost::bind(&f, b_share_temp));

	//t->join();
	//delete t;

    /*
	boost::shared_ptr<int> sp;
	sp = boost::shared_ptr<int>(new int(3));
	cout << *b_share_temp << endl;
    */

    //boost::shared_ptr<void>(new char[8]);
    //boost::shared_ptr<void>(new char);

    //cout << sizeof(boost::shared_ptr<double>(new int)) << endl;

    test_bool();

	return 0;
}

