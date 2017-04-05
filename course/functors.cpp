#include <iostream>
using namespace std;

// Functors are an alternative to function pointers
// use to pass blocks of code around
// is a struct/class that overloads operator()
// Lmabda expressions are syntatic sugar for functors

struct Test // an abstract class
{
    virtual bool operator()(string &text) = 0;
    virtual ~Test(){}
};

// we could implement lots of different Tests that all derive from Test
struct MatchTest: public Test // contains code to test some object
{   // we overload the round bracket operator
    virtual bool operator()(string &text)
    {
        return text == "lion"; //checks text is lion
    }
};


// example for some function that has to perform test on some objects
// we can pass check different kinds of tests, e.g. MatchTest
void check(string text, Test &test) //must be reference if we want polymorphism to operate correctly
{
    if(test(text)) //test is not a function, but an Object!
    {
        cout << "Text matches!" << endl;
    }
    else
    {
        cout << "No match." << endl;
    }
}

int main() // the round brackets are a special kind of operator in C++
           // can take a variable list of arguments
{
    MatchTest pred; // declare MatchTest Object predicate
    string value = "lion";
    cout << pred(value) << endl; //this does resemble a function, but it's not :D


    MatchTest m;
    check("lion", m);


    return 0;
}
