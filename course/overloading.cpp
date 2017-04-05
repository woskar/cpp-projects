#include <iostream>
using namespace std;

// Rule of three: Either implement none or all of
// - assingment operator=
// - copy constructor
// - destructor

// if you implement destructor, why should you care about the other two?
// if you have to implement the destructor, then you probably have to
// clean up memory because you have pointers involved. And when you have
// pointers, you don't want to have a shallow copy of objects
// but instead a deep copy, so you need to implement it.

class Test
{
private:
    int id;
    string name;

public:
    Test(): id(0), name("")
    { cout << "Empty Construcotr running" << endl;}

    Test(int id, string name): id(id), name(name)
    { cout << "Full Construtor running" << endl;}

    // Implement Copy constructor
    Test(const Test & other): id(other.id), name(other.name)
    { cout << "Copy Constructor running" << endl;}
    // what would also work for this constructor is
    // Test(const Test & other){*this = other;}
    // so this makes explicit use of the implemented assignment operator=

    // Destructor
    ~Test(){}

    void print(){cout << id << ": " << name << endl;}

    // Implement assignment operator
    const Test & operator=(const Test &other)
    {
        cout << "Assignment running"<<endl;
        id = other.id;
        name = other.name;
        return *this;
    }

    // Overload the left bitshift for cout
    // friend is necessary here
    friend ostream & operator<<(ostream & out, const Test & test)
    {
        out << test.id << ": " << test.name; //no endl, let the user choose
        return out;
    }
};

int main()
{
    Test test1(10, "Mike");
    test1.print();
    cout << "Print Test 1" << endl;

    Test test2(20, "Bob");

    test2 = test1;
    test2.print();
    cout << "Print Test 2" << endl;

    Test test3;
/*
    // return value of = is a reference
    // this allows operator chaining
    test3 = test2 = test1;
*/

    test3.operator=(test2); //equivalent to test3 = test2
    test3.print();
    cout << "Print Test 3" << endl;

    cout << endl;
    // Copy initialization
    // here is not called the assignment operator=
    // instead we invoke the implicit copy constructor:
    // because of this case the impl.cop.constr. is part rule of three
    Test test4 = test1;
    test4.print();
    cout << endl;

    Test test5(3, "Mary");
    cout << test5 << endl;

    return 0;
}
