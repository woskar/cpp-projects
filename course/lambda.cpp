#include <iostream>
using namespace std;

// possibilities to "pass code around"
// function pointers: bool (*funcPoint)(string test)
// functors: object (struct) with overloaded () to get&return something
// lambda expressions: [](){}; the bracket fest

// lambda expressions are compatible with function pointers
void test(void (*pFunc)()) // test is a fct that expects a func.poiner as arg
{
    pFunc(); //the round brackets call the function pFunc points to
}

// Function that takes lambda expression with parameter
void testGreet(void (*greet)(string))
{
    greet("Bob");
}

// Function that accepts pDivide2 or similar lambda expressions
void runDivide2(double (*divide)(double, double))
{
    cout << divide(15, 3) << endl;
}

// Capturing this with lambdas
class Test
{
private:
    int one{1};
    int two{2};
public:
    void run()
    {
        int three{3};
        int four{4};

        auto pLambda = [this, three, four]() //we can't capture the instance variables
        {                                    //one and two here in the same way
            cout << one << endl;             //instead we have to include this
            cout << two << endl;             //this captures always by reference!
            cout << three << endl;           //order does not matter
            cout << four << endl;
        };
        pLambda();
    }
};

int main()
{
    //[](){}; // that's a valid defiition of a lambda expression :D
    //[](parameter){action};

    // store anonymus function in variable func
    // the type will vary depending on the expression, so just use auto
    auto func = [](){cout << "hello" << endl;};
    func(); // call the function

    // lambda can be called directly as well:
    [](){cout << "hello there" << endl;}();

    // we can pass a lambda expression to a function (which takes a fucPointer)
    test(func); // lambda expr acts as if it was a fuction pointer

    // we can also put the lambda function directly into a function
    // that expects a function pointer as argument
    test([](){cout << "lambda expressions goes directly here!" << endl;});

    // define lambda that takes arguments
    auto pGreet = [](string name){cout << "Hello " << name << endl;};
    pGreet("Oskar"); //call it by providing the argument

    // pass lambda expression with parameter to funciton
    testGreet(pGreet);
    testGreet([](string name){cout << "Hello " << name << endl;});

    // lambda that has return types
    auto pDivide = [](double a, double b){return a/b;};
    cout << pDivide(42, 3.1415) << endl;

    // if there's different possible return types, we need to specify
    // using the trailing return type syntax ->
    auto pDivide2 = [](double a, double b) -> double
    {
        if(b == 0.0) return 0; // here return would be int
        else return a/b;       // here return type will always be double
    }; // don't forget ; because it's still a lambda expression!
    cout << pDivide2(12, 0) << endl;

    // pass this function into another
    runDivide2(pDivide2);

// Capture brackets

    int one = 1;
    int two = 2;
    int three = 3;

    // we want to use local variables
    // we have to capture them by passing them into the []
    [one, two](){cout << one << ", " << two << endl;}();

    // capture all local variables by value with [=]
    [=](){cout << one << ", " << two << endl;}();

    // capture all local var by value and three by reference
    // we can even change three now in the expression
    [=, &three](){three=7; cout << one << ", " << three << endl;}();
    cout << three << endl; // three was indeed changed

    // capture all local var by reference
    [&](){one=5, two=9; cout << one << ", " << two << endl;}();

    // capture all local var by reference but two and three by value
    [&, two, three](){one=2; cout << one << ", " << two << endl;}();

    cout << endl;

// Capture this with lambdas, see Test class on top
    Test test;
    test.run();
    cout << endl;

// Mutable keyword in lambda expressions
    int cats = 5;
    // with mutable, only the copy in the lambda expression is changed.
    [cats]() mutable {cats=100; cout << cats << endl;}();
    cout << cats << endl;


    return 0;
}
