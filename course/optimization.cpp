#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

// Optimizations
// memory
// r value, r value

// Optimizations:

// copy elision (return value optimization) prevents from getting
// the copy constructor run 3 times in the following:
// Test getTest(){
//     return Test()
// }
// when called:
// Test test = getTest();

/* Memory and Move constructor issues:

const int SIZE = 10;
int * pBuffer;
pBuffer = new int[SIZE];

// 3 Ways to set new allocated memory to zero:
//1) memset, params: pointer_to_Memory, value_of_bytes_to_set_to, number_of_bytes
memset(pBuffer, 0, sizeof(int)*SIZE);

// 2) in the allocation above, write ()
pBuffer = new int[SIZE](); // the () initialize all values to zero
                           // especially with C++11, {} works certainly

// 3) iterate over all Elements in buffer:
for(int i=0; i<SIZE; i++)
    pBuffer[i] = 0;

// Implement a copy constructor with memory involved:
Test(const Test &other){
    pBuffer = new int[SIZE]{};
    memcpy(pBuffer, other.pBuffer, SIZE*sizeof(int));
}

*/

class Test{
    int id;
};

Test getTest(){
    return Test(); // the return value here is an r-value
}

void check(const Test &value){ //takes l-value reference here
    cout << "lValue function!" << endl;
}

void check(Test &&value){ //takes r-value reference here
    cout << "rValue function!" << endl;
}

// whole Test class from course
class XTest {
private:
	static const int SIZE = 100;
    // initialize with Nullpointer if we don't allocate any memory
    // prevents bugs, is good practice
	int *_pBuffer{nullptr}; //only if we have memory like this one allocated
                            //we want to implement the move ..operators
                            //otherwise just take default shallow implementation

public:
	XTest() {
		_pBuffer = new int[SIZE] { };
	}

	XTest(int i) {
		_pBuffer = new int[SIZE] { };

		for (int i = 0; i < SIZE; i++) {
			_pBuffer[i] = 7 * i;
		}
	}

    // Copy constructor
	XTest(const XTest &other) {
		_pBuffer = new int[SIZE] { };
		memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));
	}

    // Move constructor
    // uses r-value-reference (&&)
    // which is mutable (no const)
    // idea is: we get some sort of temporary object here
    // somehting that's not named, an r-value
    // and we want to steal resourcs from it.
	XTest(XTest &&other) { //you can put in a check that other != this
		cout << "Move constructor" << endl;
		_pBuffer = other._pBuffer; //whatever rsources in the other, steal those
		other._pBuffer = nullptr;  //if we don't add this line, the destructor
	}                              //will take the resources away from us ;D
                                   //the nullpointer on the other hand can just
                                   //be deleted from the destructor in c++11

    // That's the normal assignment operator
	XTest &operator=(const XTest &other) {
		_pBuffer = new int[SIZE] { };
		memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));
		return *this;
	}

    // Here we have the move assignment operator:
    // takes a mutable XTest r-value reference other
    XTest &operator=(XTest &&other){
        cout << "Move assignment" << endl;
        delete[] _pBuffer; //the object we're assigning to will have already
                           //have assigned memory which we have to free up
        _pBuffer = other._pBuffer; //assign the memory to the other memory
        other._pBuffer = nullptr;  //stop other trying to delete that memory
        return *this;             //return our object (as reference)
    }

	~XTest() { delete[] _pBuffer;}

	friend ostream &operator<<(ostream &out, const XTest &test);
};

ostream &operator<<(ostream &out, const XTest &test) {
	out << "Hello from test";
	return out;
}

XTest getXTest() {
	return XTest();
}


int main()
{                   // naive and old distinction between l and r values:
    int value1 = 7; // value1 is lvalue (left to =), 7 rvalue (right to =)

    // C++11:
    // l value is anything we can take the address of (location)
    int *pValue1 = &value1; // value 1 is a lvalue
    //int *pValue2 = &7; // we can't get the location! 7 is r value.

    // Class *pInstance = &instance; // a object is a l value, works

    // Class *pInstance = &method; // we can't get loc, so it's r value
                                   // such temporary value is an r value
                                   // return types of functions ar r values

    int *pValue3 = &++value1; // that's an l value referring to 8;
    cout << *pValue3 << endl;

    //int *pValue4 = &value1++; // does not work, because postfix increment
                              // returns a temporary copy of the value so
                              // that the actual original value can be used.
                              // so value1++ is an r value.

    //int *s = &(7 + value1) // that's an temporary value, so r-value

// l-value reference: normal/old kind of reference

    // Bind a reference to an l-value test1
    Test test1;
    Test &refTest1 = test1; //this is pointing an l-val-ref at an l-value

    // Binding a reference to an r-value does not work
    //Test &refTest2 = getTest();

    // We can make it work by making it const:
    // const l-value-references can bind to r-values
    const Test &refTest3 = getTest();
    // the lifetime of the from getTest returned r-value gets extended
    // as long as the refTest3 reference exists
    // it's now no temporary reference any more

    // Constructor always has a const l value reference to it
    Test test2((Test())); //works fine
    // Test() is a r-value
    // we pass it into the copy constructor, which is l-value

// r-value references:
    // Can be used for move constructors that are a
    // lot more efficient than copy-construcotr

    // identify temporary values and handle them differently to optimize
    // double ampersand && has new meaning: r-value-reference
    Test &&rRef1 = Test(); //bind r-value-reference to r-value
    Test &&rRef2 = getTest(); // same here

    check(test1); // we get l-version running, because test1 is l-value

    check(getTest()); // we get r-version here
    check((Test()));

// Move constructors:
    // Add objects to a vector:
    vector<XTest> vec;

    //invoke the move constructor
    vec.push_back((XTest()));
    //Move constructor is running, because vector is copying the
    //XTest() object using the move constructor
    //we're not allocating any more memory in the move constructor
    //so that's much more efficient as the copy constructor.

// Move assignment operator:
    XTest testObject; //construct the object
    testObject = getXTest(); //now assign it to an r-value

    return 0;
}
