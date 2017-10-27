#include <vector>
#include <fstream>
#include <boost/foreach.hpp>
#include <iostream>
#include "addressbook.pb.h"

void serialized_to_fs(const char *fname, const std::vector<Person> &person_arr)
{
    std::ofstream ofs(fname, std::ios_base::binary);

    BOOST_FOREACH(const Person &person, person_arr)
    {
        person.SerializeToOstream(&ofs);
    }
}

void deserialized_from_fs(const char *fname)
{
    std::ifstream ifs(fname, std::ios_base::binary);

    Person p;
    p.ParseFromIstream(&ifs);
    //std::cout << p.name() << ": " << p.age() << std::endl;
}

int main(int argc, char **argv)
{
    std::vector<Person> person_arr;

    Person p;

    //p.set_name("mxl");
    p.set_age("1");
    //p.set_email("mxl");
    p.set_sex("22");
    p.set_sex1("333");

    person_arr.push_back(p);

    serialized_to_fs("1.data", person_arr);
    //deserialized_from_fs("1.data");

    return 0;
}
