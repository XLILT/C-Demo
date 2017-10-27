#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>

using namespace std;

void f()
{
	cout << "get in f" << endl;
	int *q = new int[1024 * 1024 * 2];
	memset(q, 0, sizeof(*q) * 1024 * 1024 * 2);

	cin.get();
	return;
}

struct less_compare {
	/*
	bool operator () (const int left, const int right) {
		if (left > right)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	*/
};

int main()
{
	/*
	int *p = new int[1024 * 1024 * 1];
	memset(p, 0, sizeof(*p) * 1024 * 1024 * 1);

	new boost::thread(boost::bind(&f));
	new boost::thread(boost::bind(&f));
	*/

	multimap<int, int, greater<int> > mul_map;
	mul_map.insert(pair<int, int>(1, 1));
	mul_map.insert(pair<int, int>(9, 2));
	mul_map.insert(pair<int, int>(8, 3));
	mul_map.insert(pair<int, int>(1, 2));
	mul_map.insert(pair<int, int>(2, 3));

	typedef multimap<int, int>::value_type multimap_pair;
	BOOST_FOREACH(multimap_pair &pair_mul_map, mul_map)
	{
		cout << pair_mul_map.first << ", " << pair_mul_map.second << endl;
	}

	cin.get();
	return 0;
}

