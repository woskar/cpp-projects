#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

// terminology to keep separate:
// initialization list: for constructor syntax, see class Test, include header
// initializer list: initailize variables, as in vector<int> numbers{1,2,3};

class C
{
public:
    string text;
    int id;
};

// more common for the above, aggregating data,
// would be struct which is public from the beginning:
struct S
{
    string text;
    int id;
};

// demonstrate initializer_list, see also section below
class Test
{
public:
    Test(initializer_list<string> texts)
    {   // the given list is iterable
        for(auto value: texts)
            cout << value << endl;
        // this can be used to store objects etc
    }

    void print(initializer_list<string> initList)
    {
        for(auto value: initList)
            cout << value << endl;
    }
};

// Object initialization
class Person
{
    int id{3}; // we can now have default initialization here
    string name{"Mike_default"};  // same as int id = 3; which was not possible before 11
public:
    Person() = default;   // new syntax to implement default construcotr
                          // we loose the implicit default constr. because of the next
    Person(int id): id(id){} //overwrites only one default value

    // default copy construtor: we don't have to implement anymore!
    Person(const Person & other) = default;

    // make explicit to use the default assignment operator
    Person &operator=(const Person &other) = default;

    // instead of saying default we could write "delete"
    // to get rid of e.g. copy constructor
    // and so make object not copy-able 

    void print()
    { cout << id << ": " << name << endl; }
};

int main()
{
// C++98
    int values[] = {1,4,5};
    cout << values[0]<<endl;

    C c1 = {"Hello", 7};
    cout << c1.text << endl;

    S s1 = {"Hi again", 8};
    cout << s1.text << endl;

    // anonymus type of syntax for structs if you don't wnat to use them again:
    struct //no name here!
    {
        string text;
        int id;
    } r1 = {"hey1", 9}, r2 = {"hey2", 10}; //initialisation here before ending ;

    cout << r1.text << endl;
    cout << r2.text << endl;

    vector<string> strings;
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");
    cout << endl;

// C++11
// now we can use {} everywhere to initialize things (even custom types)

    int val{}; //empty braces initialize to zero (whatever that is for the type)
    cout << val << endl;

    int value{5}; // initialize without any spaces or =
    cout << value << endl;

    int * pSomething{&value}; // works with poiners
    cout << *pSomething << endl;

    int * pElse{}; // equivalent to int *pElse = nullptr;
    cout << pElse << endl; // where nullptr is a (c++11) new Keyword for Nullpointer
                           // nullptr is different from NULL (!) and just for pointers

    string text{"Hello"}; // works with strings
    cout << text << endl;

    int numbers[]{1,2,4}; //no need to specify [3], c++11 figures it out
    cout << numbers[1] << endl;

    int array[3]{}; // will initialize all values in array to 0
    cout << array[1] << endl;

    int *pInts = new int[3]{1,2,3}; // with new we have to specify number of elements
    cout << pInts[2] << endl;
    delete[] pInts;

    vector<string> words{"one", "two", "three"};
    cout << words[2] << endl;

    struct {
        string text;
        int id;
    } v1{"hey1", 9}, v2{"hey2", 10}; //now you can miss out =

    cout << v1.text << endl;
    cout << v2.text << endl;
    cout << endl;

// Initializer list

    Test test{"apple", "orange", "banana"};
    cout << endl;

    // Magic: pass an array to a function without having to declare the array first
    test.print({"one", "two"});

// Object Initialization, using custom classes
    Person testPerson;
    testPerson.print(); // here we got a default initialization
    Person testPerson2(42);
    testPerson2.print();
    Person testPerson3(100);

    Person testPerson4 = testPerson2; //this invokes copy constructor
    testPerson3 = testPerson4; // this invokes the assignment operator
    return 0;
}
