#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void print(int elem)
{
	cout << elem << ' ';
}

int main()
{
	vector<int> coll;
	int n;
	
	while(cin >> n && n)
	{
		coll.push_back(n);
	}
	
	make_heap(coll.begin(), coll.end());
	cout << "After make_heap()" << endl;
	for_each(coll.begin(), coll.end(), print);
	cout << endl;
	
	cin >> n;
	coll.push_back(n);
	push_heap(coll.begin(), coll.end());
	
	cout << "After push_heap()" << endl;
	for_each(coll.begin(), coll.end(), print);
	cout << endl;
	
	pop_heap(coll.begin(), coll.end());
	cout << "After pop_heap()" << endl;
	for_each(coll.begin(), coll.end(), print);
	cout << endl;
	
	cout << "coll.back() : " << coll.back() << endl;
	coll.pop_back();
	
	sort_heap(coll.begin(), coll.end());
	cout << "After sort_heap()" << endl;
	for_each(coll.begin(), coll.end(), print);
	cout << endl;
	
	return 0;
}

