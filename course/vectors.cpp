#include <iostream>
#include <vector>
using namespace std;

class Test
{
private:
    int id_;
    string name_;
public:
    Test(int id, string name):id_(id), name_(name){}

    void print() {cout << id_ <<" " << name_ << endl;}

    bool operator<(const Test &other) const
    {
        return name_ < other.name_;
    }


    // comparing function, see below
    friend bool comp(const Test &a, const Test &b);
};

bool comp(const Test &a, const Test &b)
{
    return a.id_< b.id_;
    // name_ is private, but we have friend-ed the function
    // so we can access private member variables!
}


int main()
{
    // vector is a template class
    // type of object has to be specified in <>
    // vector is basically a resizable array
    vector<string> strings(1); //five vectors of type string
    strings[0] = "dog"; //Bracket[]-operator is overloaded for vector class
    cout << strings[0] << endl;

    // vector cares about memory automatically
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    cout << strings.size() << endl;

// iterate over vector
    // naive, but not recommended syntax:
    for(int i=0; i<strings.size(); ++i)
        cout << strings[i] << endl;

    // using iterators:
    vector<string>::iterator it = strings.begin();
    cout << *it << endl; //iterator overloads the star operator, like dereferencing pointers
    it++; // iterator overloads the increment operator, sets it to next element
    cout << *it << endl;

    //use iterator in loop:
    for(vector<string>::iterator iter = strings.begin(); iter!=strings.end(); ++iter)
    {
        cout << *iter << endl;
    }

// Memory aspects:
    // vector manages an array internally, which it doubles when boundary reached.
    vector<double> numbers(0);
    cout << "Size: " << numbers.size() << endl;

    int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;
    for(int i = 0; i<1000; ++i)
    {
        if(numbers.capacity()!=capacity)
        {
            capacity = numbers.capacity();
            cout << "Capacity: " << capacity << endl;
        }
        numbers.push_back(i);
    }
    numbers.clear(); //will delete all elements, capacity stays the same
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;

    numbers.resize(100); //reserve does not change capacity either
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;

    numbers.reserve(2000); //reserve does not change capacity either
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;

// Two dimensional vectors:
    //first is containing the rows, the second is a row, so makes up columns
    vector< vector<int> > grid(3, vector<int>(4, 0));

    for(int row=0; row < grid.size(); ++row)
    {
        for(int col=0; col < grid[row].size(); ++col)
        {
            cout << grid[row][col] << " " << flush;
        }
        cout << endl;
    }
    cout << endl;

    // iterate over 2D-Vector-Matrix with iterators :D
    vector< vector<int> >::iterator itrow = grid.begin();
    for(; itrow!=grid.end(); ++itrow)
    {
        vector<int>::iterator itcol = (*itrow).begin();
        for(; itcol!=(*itrow).end(); ++itcol)
        {
            cout << *itcol << " " << flush;
        }
        cout << endl;
    }
    cout << endl;
    // sort a vector
    vector<Test> tests;
    tests.push_back(Test(5, "Mike"));
    tests.push_back(Test(15, "Sue"));
    tests.push_back(Test(53, "Raj"));
    tests.push_back(Test(1, "Vicky"));

    // sort gets iterators for where to act, doesn't have to be whole vector
    // could also be sort(tests.begin()+1, test.begin()+3)
    // the sort algorithm does it's work, if there is an overloaded operator< in the custom Class
    sort(tests.begin(), tests.end());
    for(vector<Test>::iterator it = tests.begin(); it != tests.end(); ++it)
        it-> print();
    cout << endl;

    // if we haven't implemented < in the class, we can provide a function(pointer)
    sort(tests.begin(), tests.end(), comp);
    for(vector<Test>::iterator it = tests.begin(); it != tests.end(); ++it)
        it-> print();
    cout << endl;

    return 0;
}
