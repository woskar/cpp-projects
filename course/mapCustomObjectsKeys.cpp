#include <iostream>
#include <map>
using namespace std;

// we create a map and have our custom  Class objects as keys

class Person
{
private:
    string name_;
    int age_;

public:
    Person():name_(""), age_(-1) {}

    Person(string name, int age): name_(name), age_(age) {}

    // Custom Copy Constructor
    Person(const Person &other): name_(other.name_), age_(other.age_){}

    void print() const // we have to mark it const because of the const keys given by iterator, see below
    {
        cout << name_ << ": " << age_ << flush;
        // it's better to flush in print method instead of endl
        // leave the endl for the caller of the method
    }

    // Implement overloading of the Less than operator
    bool operator<(const Person &other) const //&Reference for efficiency, to not copy other
    {                                         //const Person to not change the other object
        // we want to compare our objects     //() const to not change the (this)object acted on

        if(name_ == other.name_)
        {
            // if names are equal, compare age
            return age_ < other.age_;
        }
        else
        {
            // else compare by given name
            return (*this).name_ < other.name_;
            // the < does lexicographical comparison on the strings
        }
    }

};



int main()
{
    map<Person, int> people;

    // C++ does not know how to sort the keys in the map (what it wants to do),
    // because we have to tell how to sort our custom objects.
    // therefore we had to implement the overloaded operator<
    people[Person("Mike", 40)] = 40;
    people[Person("Sue", 20)] = 20;
    people[Person("Sue", 20)] = 200;  // adding value with same key will update/overwrite old element
    people[Person("Sue", 222)] = 100; // now a new element will be added, because of different ages in key
                                      // note that this only happens because we have operator< for age and name!
    people[Person("Raj", 30)] = 30;


    for(map<Person, int>::iterator it = people.begin();
        it!=people.end(); ++it)
    {
        cout << it -> second << ": " << flush;
        // the keys in a map are returned as const from iterator
        it -> first.print();
        cout << endl;
    }

    return 0;
}
