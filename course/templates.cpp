#include <iostream>
#include "ring.h"
using namespace std;

// template classes allow to design classes
// that work with types of variables taht the user can specify

// common use: storing custom types

// vector is a template class
// therefore member of the Standard Template Library

// with templates, C++ has to see both the definition and
// the implementation all together before it can compile the code
// because behind the scenes, c++ is creating the particular classes you need
// therefore no separation of prototypes in header and implementation
// so define all template classes in one header file

template<class T> // T is the Type the user can specify
class Test        // in our Class we can now use T as if it was a defined datatype
{
private:
    T obj;
public:
    Test(T obj)
    {
        this->obj = obj;
    }

    void print()
    {   // if we assume that T has the stream insertion operator implemented
        cout << obj << endl;
    }
};

// template functions

// start with a regular function
void print(int n)
{
    cout << "non-template version: "<< n << endl;
}

// turn it into a template function
template <typename T> //instead of typename, you could again use class
void print(T n)
{
    cout << n << endl;
}

template <class T>
void show() // here we don't give T as argument
{           // therefore we have to specify which one we want to use
    cout << T() << endl;
}

template <typename T, typename K> //multiple Types possible
void output(T t, K k)
{
    cout << t << " " << k << endl;
}



int main()
{
    // use a template class
    Test<string> test1("Hello");
    test1.print();


    print(5); // call regular function

    print<string>("Hello there"); //call template function
    print<double>(42);
    print("Hi there again"); //we don't even need to specify the <type>!
    print('c'); //C++ infers the type you mean from the given argument

    print(7); //since we have a version for natural int implemented, c++ will prefer it
    print<>(8); //diamond brackets are enough to invoke the template version of the function

    //show(); //this won't compile, C++ doesn't know what to choose
    show<double>(); //this works, we have to tell the type

    output("Hi", 5);
    cout << endl;

// Working with Ring/circular buffer defined in Ring.h

    ring<string> textring(3);

    textring.add("one");
    textring.add("two");
    textring.add("three");
    textring.add("four"); //this should overwrite one in the ring

    // index based for loop works C++ 98 style
    for(int i=0; i<textring.size(); i++)
        cout << textring.get(i) << endl;
    cout << endl;

    // iterator based for loop works
    for(ring<string>::iterator it = textring.begin(); it!=textring.end(); it++)
        cout << *it << endl;
    cout << endl;

    // range based for loop works C++ 11 style
    for(auto item: textring)
        cout << item << endl;
    cout << endl;

    return 0;
}
