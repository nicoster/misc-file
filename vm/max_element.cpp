#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <boost/bind.hpp>

using namespace boost;
using namespace std;

struct Person
{
    Person(const string& _name, int _age)
        : name(_name), age(_age)
    {}
    int age;
    string name;
};

int main()
{
    list<Person> col;
    list<Person>::iterator pos;

    col.push_back(Person("Tom", 10));
    col.push_back(Person("Jerry", 12));
    col.push_back(Person("Mickey", 9));

    Person eldest = 
        *max_element(col.begin(), col.end(), 
            bind(&Person::age, _1) < bind(&Person::age, _2));
    
    cout << eldest.name;
}
