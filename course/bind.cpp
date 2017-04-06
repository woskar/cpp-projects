#include <iostream>
#include <functional> // bind

// bind can "bind", preset arguments/parameters of functions

using namespace std;
using namespace placeholders; // in functional header

int add(int a, int b, int c) {
    cout << a << ", " << b << ", " << c << endl;
    return a + b + c;
}

class Test {
public:
	int add(int a, int b, int c) {
		cout << a << ", " << b << ", " << c << endl;
		return a + b + c;
	}
};


int run(function<int(int, int)> func) {
	return func(7, 3);
}

int main() {

    cout << add(1,2,3) << endl;

    auto calculator = bind(add, 3,4,5); // also possible &add, but optional
    // calculator will now call with the previously supplied arguments
    cout << calculator() << endl;

    // if we put _1 etc in, they act as placeholders, we have to give them later
    auto calculator2 = bind(add, _1, _2, _3);
    cout << calculator2(10, 20, 30) << endl;
    // the numbers _1, _2 represent the order of passed arguments

    auto calculator3 = bind(add, _2, 100, _1); //creates a bound alias of add function again
    cout << calculator3(1,1) << endl;

    //a function taking a function works with this as well:
    cout << run(calculator3)<< endl; //arguments match there

    //We can bind to methods as well

	Test test; //we need object of the class to bind to
    auto calculate = bind(&Test::add, test, _2, 100, _1); //& is obligatory here
	cout << run(calculate) << endl;

	return 0;
}
