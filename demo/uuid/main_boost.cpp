#include <stdio.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <iostream>

using namespace boost;
using namespace boost::uuids;
using namespace std;

::uint64_t SttGetUsTickCount()
{
    uint64_t currentTime;

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

    static LARGE_INTEGER TicksPerSecond = {0};
    LARGE_INTEGER Tick;

    if(!TicksPerSecond.QuadPart)
    {
        QueryPerformanceFrequency(&TicksPerSecond);
    }

    QueryPerformanceCounter(&Tick);

    int64_t Seconds = Tick.QuadPart/TicksPerSecond.QuadPart;
    int64_t LeftPart = Tick.QuadPart - (TicksPerSecond.QuadPart*Seconds);
    int64_t uSeconds = LeftPart*1000*1000/TicksPerSecond.QuadPart;
    currentTime = Seconds*1000*1000+uSeconds;
#endif


#if defined(linux) || defined(__linux) || defined(__linux__)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    currentTime = (ts.tv_sec * 1000*1000 + ts.tv_nsec / 1000);
#endif

    return currentTime;
}

int main(int argc, char **argv)
{	
	uint64_t start = SttGetUsTickCount();
	char *p = new char[1024];
	//memset(p, 0, sizeof(int) * 1024 * 1024);
	//for(int i = 0; i < 1024; i++)
	//{
	//	cout<<char[i]<<", ";
	//}
	//delete []p;
	random_generator rgenerator;
	uuid a_uuid = rgenerator();    	
	uint64_t end = SttGetUsTickCount();	
	cout<<a_uuid<<", "<<end - start<<"us"<<endl;	
		
	return 0;
}
