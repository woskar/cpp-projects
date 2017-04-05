#include <iostream>
using namespace std;

//discussed here: object slicing and polymorphism
// object slicing = upcasting object types, see on bottom.
class Parent
{
private:
    int one;
public:
    Parent(): one(0){}

    //Copy constructor
    Parent(const Parent & other) // when we define only this constructor
    :one(other.one)              // we loose the implicit default constructor
                                 // and have to define the above default one.
    {cout << "copy parent" << endl;}

    virtual void print(){cout << "parent" << endl;}

    virtual ~Parent(){}
};

class Child: public Parent
{
private:
    int two;
public:
    Child(): two(0){}// we can't set one here, because that's private in the super class
                     // instead the Parent constructor is automatically run.
    void print(){cout << "child" << endl;}
};

int main()
{
    Child c1; // create Child object
    Parent &p1 = c1; // create Parent reference pointing to child

    p1.print(); // only with added "virtual" in base class parent,
                // we get the right output from child-class, namely child
                // whithout virtual then parent is output
                // with virtual the right method will be invoked
                // this is polymorphism, works also for pointers.

    Parent p2 = Child(); // here parent Copy constructor is invoked
                         // here we do "object slicing"
                         // we can't make use of the child variables
                         // "upcasting" a child object to parent type
                         // up: going up in hierarchy,
                         // casting: changing type
    p2.print();
    return 0;
}
