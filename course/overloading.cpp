#include <iostream>
using namespace std;

class Test
{
private:
    int id;
    string name;

public:
    Test(): id(0), name(""){}
    Test(int id, string name): id(id), name(name)
    { cout << "Construtor runs" << endl;}

    void print(){cout << id << ": " << name << endl;}

    const Test & operator=(const Test &other)
    {
        cout << "Assignment running"<<endl;
        id = other.id;
        name = other.name;
        return *this;
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
    Test test4 = test1;
    test4.print();

    return 0;
}
