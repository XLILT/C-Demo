#include <fstream>
#include <map>
#include <iostream>
#include <boost/foreach.hpp>

typedef std::map<std::string, int>::value_type PersonValuetype;

void serialized_to_fs(const char *fname, const std::map<std::string, int> &person)
{
    std::ofstream ofs(fname, std::ios_base::binary);

    BOOST_FOREACH(const PersonValuetype &cvt, person)
    {
        ofs.write(cvt.first.c_str(), cvt.first.length() + 1);
        ofs.write(reinterpret_cast<const char *>(&(cvt.second)), sizeof(cvt.second));
    }
}

void deserialized_from_fs(const char *fname)
{
    std::ifstream ifs(fname, std::ios_base::binary);

    std::map<std::string, int> person;

    std::string name;
    int c = ifs.get();
    while(c != std::char_traits<char>::eof())
    {
        if(c == 0)
        {
            int age = 0;
            ifs.read(reinterpret_cast<char *>(&age), sizeof(age));

            person[name] = age;

            name.clear();
        }
        else
        {
            name += c;
        }

        c = ifs.get();

        //std::cout << c << ", " << name << std::endl;
    }

    BOOST_FOREACH(const PersonValuetype &cvt, person)
    {
        std::cout << cvt.first << ": " << cvt.second << std::endl;
    }
}

int main(int argc, char **argv)
{
    std::map<std::string, int> person_map;
    person_map["mxl"] = 28;
    person_map["cx"] = 27;

    //serialized_to_fs("1.data", person_map);
    deserialized_from_fs("1.data");
    return 0;
}
