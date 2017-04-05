#include <iostream>
#include <map>
using namespace std;

// we create a map and have our custom  Class objects as vlaues

class Person
{
private:
    string name_;
    int age_;

public:
    Person():name_(""), age_(-1) {}

    Person(string name, int age): name_(name), age_(age) {}

    // Custom Copy Constructor
    Person(const Person &other): name_(other.name_), age_(other.age_)
    {cout << "Copy Constructor running" << endl;}

    void print()
    {
        cout << name_ << ": " << age_ << endl;
    }
};



int main()
{
    map<int, Person> people;

    // watch out! what happens here is
    // Map is creating new object with parameterless (default)constructor
    // then Values e.g. Mike, 40 are then assigned using assingment operator (=)
    // the default implementation of assignment operator is used
    // this does a shallow copy, so copies values of instance variables
    // if we had pointers in our object, we would not want this
    // then we had to overwrite the assignment operator
    people[20] = Person("Mike", 40);
    people[13] = Person("Rob", 30);
    people[2] = Person("Andre", 20);

    // only if we run this line, our custom copy constructor is run
    //people.insert(make_pair(55, Person("Bob", 45)));


    for(map<int, Person>::iterator it = people.begin();
        it!=people.end(); ++it)
    {
        cout << it -> first << ": " << flush;
        it -> second.print();
    }

    return 0;
}
