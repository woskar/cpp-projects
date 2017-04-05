#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Stack is Last in First out, stack or pile of plates
// add items via s.push()
// remove items via s.pop() (no return type)
// get element on top with s.top()

// Queue is First in First out, queue in supermarket
// get first added element q.front()
// get last added element q.back()
// add item (on the back) s.push()
// remove item (from front) s.pop()

// there is also a "deque" in STL
// which is a double ended queue
// where insert can be at both ends etc


class Test
{
    string name;

public:
    Test(): name("") {}
    Test(string name): name(name) {}
    ~Test() {
        //cout << "Object destroyed" << endl;
    }

    void print() const
    {
        cout << name << endl;
    }

    bool operator<(const Test &other) const
    {
        return name < other.name;
    }
};

int main()
{
    stack<Test> testStack;
    testStack.push(Test("Mike"));
    // when adding, the objects are destroyed and
    // created again on the stack, see also below
    testStack.push(Test("John"));
    testStack.push(Test("Sue"));

    cout << "---end of creating---" << endl;

    Test test1 = testStack.top();
    test1.print();

    testStack.pop();
    Test test2 = testStack.top();
    // .top() returns reference to object on top
    // Test test2 creates a new Object with default constructor
    // with "=" the default copy constructor is invoked
    // copies the object the reference refers to into the new object
    // and shallow-copys the instance variables over in the just created test2 Object
    test2.print();

    /*
    // we could receive a reference:
    Test &test3 = testStack.top();
    testStack.pop(); // this destroys the object
    test3.print();   // wrong!! don't use reference to destroyed object!
    */               // Reference is invalidated!

    cout << endl;
    stack<Test> testStack2;
    testStack2.push(Test("Mike"));
    testStack2.push(Test("John"));
    testStack2.push(Test("Sue"));

    // loop through a stack
    // can only be done by popping elements off
    while(testStack2.size() > 0)
    {
        Test &test = testStack2.top();
        test.print();
        testStack2.pop();
    }

///// QUEUE ///////

    cout << endl;
    queue<Test> testQueue;
    testQueue.push(Test("Mike"));
    testQueue.push(Test("John"));
    testQueue.push(Test("Sue"));

    testQueue.back().print();
    cout << endl;

    // iterating is same as with stack, but now .front instead of .top()
    while(testQueue.size() > 0)
    {
        Test &test = testQueue.front();
        test.print();
        testQueue.pop();
    }


    cout << "--End of Program---" << endl;

    return 0;
}
