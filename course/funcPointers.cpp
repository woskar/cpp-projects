#include <iostream>
#include <vector>
#include <algorithm> //for count_if
using namespace std;

// alternative to Function Pointers are Lambda Expressions since C++11

// when using virtual, a virtual table is created
// which is a table of function pointers
// when you call a method in the child class via a pointer to the
// parent class type, C++ will look up on a table of function Pointers
// the right function to call.


void test()
{
    cout << "Hello" << endl;
}

void test2(int value)
{
    cout << "My value is " << value << endl;
}

// Create function that takes checks if stringlength is 3
bool match(string test)
{
    return test.size() == 3;
}

// implement our own version of count_if
int countStrings(vector<string> & texts, bool (*funcPoint)(string test))
{
    int count = 0;
    for(vector<string>::iterator it=texts.begin(); it!=texts.end(); ++it)
    {
        if(funcPoint(*it))
            count++;
    }
    return count;
}

int main()
{
    test(); // calls test directly

    // Anatomy of a funtion Pointer:
    // Returntype (*VariableName)(ParameterList)
    void (*pTest)();

    // point our function Pointer to the Function:
    pTest = &test; // we could leave out the address symbol &, because it's not ambiguous
                   // all we need is the name of a function
                   // a name of a function is the name to that funcion!

    // how to call it:
    (*pTest)(); // calls test via the function Pointer pTest
                // we don't even need the dereference * here
                // because if we add brackets () to a pointer to a function
                // it's obvious that you intend to call the function the pointer points to

    //note: the brackets () are necessary to have the right precedence.
    // *pTest(); could also dereference a pointer returned by the function call pTest();
    // to resolve ambiguity, we need to have the brackets.

    // so in short, we can have:
    void (*pTest2)() = test; //create a Function pointer
    pTest2(); // call the function the funcpointer points to

    // having a function that takes parameters:
    void(*pTest3)(int) = test2; //we only have to specify the types of the parameters
    pTest3(42);


    vector<string> texts;
    texts.push_back("one");
    texts.push_back("two");
    texts.push_back("three");
    texts.push_back("four");
    texts.push_back("five");
    texts.push_back("six");
    texts.push_back("seven");

    // count_if takes iterators and function with bool returntype
    cout << count_if(texts.begin(), texts.end(), match) << endl;

    // custom implementation of count_if
    cout << countStrings(texts, match) << endl;

    return 0;
}
