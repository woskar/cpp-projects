#include <iostream>
#include <vector>
using namespace std;

// enhanced for loops are range based for loops
// on this topic see also ring.h where a custom iterator is implemented

int main()
{
    auto texts = {"one", "tow", "three"}; // would be char texts[] without auto

    // enhanced for loop:
    for(auto text: texts)
    {
        cout << text << endl;
        cout << typeid(text).name() << endl;
    }

    vector<int> numbers;
    numbers.push_back(5);
    numbers.push_back(1);
    numbers.push_back(7);
    numbers.push_back(3);

    for(auto number:numbers)
    {
        cout << number << endl;
    }

    string hello = "Hello";
    for(auto c: hello)
    {
        cout << c << endl;
    }

    return 0;
}
