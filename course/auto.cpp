#include <iostream>
#include <typeinfo> //for TypeID
using namespace std;

// auto replaces the type declaration of a variable
// e.g. when initializing variables


// auto works for functions as well
// -> is followed by return type, called trailing return type
auto test() -> int
{
    return 100;
}

// useful e.g. in Template functions:
template <class T, class S>
auto add(T val1, S val2) -> decltype(val1 + val2)
{
    return val1+val2;
}

int get() // just some small function
{
    return 999;
}

// auto works with functions as well
auto func() -> decltype(get())
{
    return get();
}

int main()
{
    int value1;
    double value2;
    string value3;

    //typeid is an operator and creates an object
    cout << typeid(value1).name() << endl; //outpus i
    cout << typeid(value2).name() << endl; //outputs d
    cout << typeid(value3).name() << endl; //outputs NSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE
                                           // that's name mangling here

    // decltype allows to declare variables of an existing type
    // it replaces with the type of the given variable
    decltype(value3) name = "Bob";
    cout << typeid(name).name() << endl;

    // auto replaces the type declaration of a variable
    auto value = 7;
    auto text = "Hello there";
    cout << value << endl;
    cout << text << endl;
    cout << test() << endl;
    cout << add(5.1, 42) << endl;
    cout << func() << endl;

    return 0;
}
