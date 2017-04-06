#include <iostream>
#include <memory>
using namespace std;

// Unique Pointers are a kind of smart pointers that
// handle the dealocation of memory atuomatically

// Shared pointer are similar,
// but don't delete the memory associated with the objects
// until all the pointers that point at that object have gone out of scope
// at the moment, they can point to individual objects, but not arrays

class Test {
public:
	Test() {
		cout << "created" << endl;
	}

	void greet() {
		cout << "Hello" << endl;
	}

	~Test() {
		cout << "destroyed" << endl;
	}
};

class Temp {
private:
    // we create the variable of type unique pointer here
	unique_ptr<Test[]> pTest;
public:
    // Here we must use the constructor initialization list
	Temp(): pTest(new Test[2]) {}
    // We no longer need a destructor here
    // because unique ptr will clean up when out of scope
};

int main() {
{
// unique_ptr
    unique_ptr<int> pValue(new int);
    // unique_ptr<int> is Template class, so specify <int>
    // knows that it is pointer, so no *
    // call it pTest
    // memory allocation within constructor brackets ()

    // we can use it like a pointer we already know
    // will allocate and deallocate memory automatically
    *pValue = 7;

    // Testclass will show when memory is deallocated,
    // constructor will be called automatically
    {
    // create Pointer to custom class
    unique_ptr<Test> pTestClass(new Test);
    pTestClass -> greet();
    }
    // when unique Pointer goes out of scope, so when hitting the }
    // then memory is automatically deallocated.
    // unique_ptr is the new version of auto_pointer(thats now deprecated)
    {
    // unique_ptr can be used on arrays as well
    unique_ptr<Test[]> pTestArray(new Test[3]);
    pTestArray[1].greet();
    }

    // when we create a temp instance now,
    // we get objects of class Test created
    Temp temp;
}
    cout << endl;

// shared_ptr
    shared_ptr<Test> pointTest1(new Test());

    shared_ptr<Test> pointTest3(nullptr); // initialize as nullpointer
    {
    // best way to create a shared pointer by using shared macro:
    // this is more efficient than using new yourself
    shared_ptr<Test> pointTest2 = make_shared<Test>();

    // create another shared pointer that points at the last one
    pointTest3 = pointTest2;
    // now the memory will only be destroyed when both go out of scope
    // that is only when the last } is hit, because pointTest3 is
    // outside the inner curly brackets.

    // another pointer can easily created with auto
    auto pointTest4 = pointTest2;
    }

	cout << "Program ending" << endl;

	return 0;
}
