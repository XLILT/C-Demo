#include "stdafx.h"
#include <boost/lambda/lambda.hpp>

int main(int argc, char **argv)
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    //std::for_each(vec.begin(), vec.end(), ((std::cout << boost::lambda::_1), cout << " "));
    std::for_each(vec.begin(), vec.end(), boost::lambda::_1);
    //std::for_each(vec.begin(), vec.end(), boost::lambda::_1 = 1);

    return 0;
}
