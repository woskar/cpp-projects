#include <iostream>
using namespace std;

// Perfect Forwarding
// reference collapsing
// is used internally in c++, not that common in development

class Test {

};

// call check function, which exists in two versions
// the function will tell us wich gets called
template<typename T>
void call(T &&arg) {
    //check(arg); // passes wrong value
    //check(static_cast<T>(arg)); // passes right value, because of collapsing
    check(forward<T>(arg));
}

void check(Test &test) {
	cout << "lvalue" << endl;
}

void check(Test &&test) {
	cout << "rvalue" << endl;
}


int main()
{
    //Some sort of type declaration here:
    auto &&t1 = Test(); //auto could just be test, we get r-value reference

    Test test; //create an l-value
    auto &&t2 = test; //does work, because of a reference collapsing rule in C++11
    // if auto boiled down to l-value reference type
    // then the reference as a whole would collaps
    // just leaving a l-value reference left
    // so in our example it binds to an l-value.

    call(Test()); // pass in an r-value
    call(test); // pass in an l-value


    return 0;
}
