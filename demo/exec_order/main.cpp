/*************************************************************************
    > File Name: main.cpp
    > Author: mxl2
    > Mail: xiaolongicx@gmail.com
    > Created Time: Fri 21 Apr 2017 03:25:29 PM CST
 ************************************************************************/

#include<iostream>
#include <boost/serialization/singleton.hpp>

using namespace std;

template <typename T>
struct A
{
    static T *instance()
    {
        static T a;
        _object_creator.do_nothing();

        return &a;
    }

    struct object_creator
    {
        object_creator()
        {
            A<T>::instance();
        }

        inline void do_nothing() const {}
    };

    static object_creator _object_creator;
};

template <typename T> typename A<T>::object_creator A<T>::_object_creator;

struct B
{
    B()
    {
        cout << "B is constructed" << endl;
    }
};

typedef A<B> BSingleton;

class C
{
public:
    C()
    {
        cout << "C is construected" << endl;
    }
};

typedef boost::serialization::singleton<C> CSingleton;

int main() 
{
    std::cout << "run main" << std::endl;
    BSingleton::instance();
    CSingleton::get_const_instance();

    return 1;    
}

