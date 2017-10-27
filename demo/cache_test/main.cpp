#include "stdafx.h"
#include "DataPointerCached.h"
#include <boost/shared_ptr.hpp>

int main()
{
	DataCached< boost::shared_ptr<int> > *date_cache = new DataCached< boost::shared_ptr<int> >;
	
	boost::shared_ptr<int> tm1(new int(1));
	boost::shared_ptr<int> tm2(new int(2));
	boost::shared_ptr<int> tm3(new int(3));
	boost::shared_ptr<int> tm4(new int(4));

	date_cache->add_set("set1", 100);

	date_cache->set("set1", "1", tm1);
	date_cache->set("set1", "2", tm2);
	date_cache->set("set1", "3", tm3);
	date_cache->set("set1", "4", tm4);

	const boost::shared_ptr<int> *tmp = date_cache->get("set1", "2");
	printf("%d\n", **tmp);
	
	delete date_cache;
	return 0;
}
