#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <set>
#include <sstream>


using namespace std;

class Animal
{
public:
    Animal(const string& theName):name(theName){}
    virtual ~Animal(){}
    virtual void speak() const
    {
        cout << "I do not speak." << endl;
    };

    const string& name;
    const string& getName() const {return name;}
};

class Dog : public Animal
{
public:
    Dog(const string& n):Animal(n){}
    virtual ~Dog(){}
    virtual void speak() const
    {
        cout << "Woof. I am " << getName() << endl;
    }
};

class Zoo
{
public:
    set<Dog*> dogs;
    void addAnimal(Animal* a)
    {
        Dog* d;
        if((d = dynamic_cast<Dog*>(a)))
        {
            dogs.insert(d);
        }else
        {
            //throw runtime_error("Unknown animal");
            cout << "Unknown animal" << endl;
        }
    }
};

int main()
{
    //const Animal &a = Dog("dog1");
    //const Animal &a = Animal("dog1");
    //const Dog &d = dynamic_cast<const Dog &>(a);
    //d.speak();
    Dog * p_dog = (Dog *)NULL;
    if (p_dog == NULL)
    {
        stringstream ss;
    }

    return 0;
}
