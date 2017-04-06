#include <iostream>
#include <functional>
#include <vector>
#include <algorithm> //count_if
using namespace std;

// Standard Function Type lets define reference to any callable type

// create a function to pass later as function pointer
bool check(string & test)
{
    return test.size() == 3;
}

// create a functor
class Check
{
public:
    bool operator()(string &text)
    {
        return (text.size()==3);
    }
};

// create our own functional, (that behaves like the tested count_if)
// make it take functionals take strings and return bool
void run(function<bool(string&)> check)
{
    string test = "dog";
    cout << check(test) << endl;
}

int main()
{
    int size = 3;
    vector<string> vec{"one", "tow", "three"};

    // pass count_if a lambda expression
    auto lambda = [size](string test){return test.size()==size;};
    int count = count_if(vec.begin(), vec.end(), lambda);
    cout << count << endl;

    // pass count_if a function pointer
    int count2 = count_if(vec.begin(), vec.end(), check);
    cout << count2 << endl;

    // pass a functor
    Check checker; // create a functor object
    int count3 = count_if(vec.begin(), vec.end(), checker);
    cout << count3 << endl;

    // so we can pass count_if anything that is callable,
    // so anything that has round brackets at the end.

    // we created our own functional run, now pass it the callables:
    run(lambda); // lambda expression
    run(check);  // function pointer
    run(checker);// functor

    // use syntax to define local variables
    function<int(int, int)> add = [](int one, int two){return one+two;};
    cout << add(2, 3) << endl;

     
    return 0;
}
