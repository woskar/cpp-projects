#include <iostream>
#include <set>
using namespace std;

// sets only store unique elements

// Insert custom classes into sets:
class Test
{
    int id;
    string name;

public:
    Test(): id(0), name("") {}
    Test(int id, string name): id(id), name(name) {}

    void print() const
    {
        cout << id << ": " << name << endl;
    }

    bool operator<(const Test &other) const
    {
        if(name == other.name)
        {
            return id<other.id;
        }
        else
        {
            return name < other.name;
        }
    }
};

int main()
{
    set<int> numbers;

    numbers.insert(3);
    numbers.insert(5);
    numbers.insert(1);
    numbers.insert(42);
    numbers.insert(50);
    numbers.insert(5); //this will have no effect

    for(set<int>::iterator it = numbers.begin(); it!=numbers.end(); ++it)
    {
        cout << *it << endl;
    }

    // Find elements with the .find() which returns an iterator
    set<int>::iterator itFind = numbers.find(142);
    if(itFind != numbers.end())
    {
        cout << "Found: " << *itFind << endl;
    }
    else // the returned operator run off the list
    {
        cout << "Element not found." << endl;
    }

    // Simpler way of fining elements in sets
    if(numbers.count(50)) // count can be only 1 or 0 in set, all elements unique
    {                     // and 1 does mean true, so the code works :D
        cout << "Number found." << endl;
    }

// Custom Objects in a set
    set<Test> tests;
    tests.insert(Test(10, "Mike"));
    tests.insert(Test(20, "Joe"));
    tests.insert(Test(20, "Joe"));
    tests.insert(Test(30, "Sue"));
    tests.insert(Test(40, "Sue"));

    for(set<Test>::iterator it = tests.begin(); it!=tests.end(); ++it)
    {
        it->print();
    }



    return 0;
}
